#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
	this->relation = r;
	this->capacity = 100;
	this->nrElements = 0;
	this->elements = new TElem[this->capacity];
	this->nextPosition = new int[this->capacity];
	this->firstEmpty = 0;
	this->head = -1;

	for (int index = 0; index < this->capacity - 1; index++)
	    this->nextPosition[index] = index + 1;

	this->nextPosition[this->capacity - 1] = -1;
}
//Theta(capacity)

void SortedMultiMap::add(TKey c, TValue v) {
    if (this->nrElements == this->capacity)         // if the multimap is full we need to resize it
        this->resize();

    int current = this->head;
    int previous = -1;

    while (current != -1 && !this->relation(c, this->elements[current].first)) {            // find the correct position to place the pair in the sorted multimap
        previous = current;
        current = this->nextPosition[current];
    }

    int newPosition = this->firstEmpty;                                 // the position where we place the pair in the elements array is the first empty one
    this->firstEmpty = this->nextPosition[this->firstEmpty];            // go to the next empty position
    this->elements[newPosition].first = c;
    this->elements[newPosition].second = v;                             // place the pair

    if (this->nrElements == 0) {
        this->nextPosition[newPosition] = -1;                           // if the sorted multimap is empty
        this->head = newPosition;
    }
    else if (current == -1) {
        this->nextPosition[newPosition] = -1;                           // if the position where we need to place the pair is the last one
        this->nextPosition[previous] = newPosition;
    }
    else if (current == this->head) {
        this->nextPosition[newPosition] = this->head;                   // if we need to insert on the first position and the multimap is not empty
        this->head = newPosition;
    }
    else {
        this->nextPosition[newPosition] = this->nextPosition[previous];     // else, if we need to insert between 2 pairs
        this->nextPosition[previous] = newPosition;
    }

    this->nrElements++;
}
//Best case: Theta(1), Worst case: Theta(capacity) => Total complexity: O(capacity) (best case if the multimap is empty or the key is the first, worst case if the key is on the last position)
                                                                                 // (sometimes we need to resize the multimap and the array with links, which has a complexity of Theta(newCapacity))

vector<TValue> SortedMultiMap::search(TKey c) const {
    vector<TValue> values;
    int current = this->head;
    bool found = false;
    bool stop = false;

    while (current != -1 && !stop) {
        if (this->elements[current].first == c && found)            // we can stop if we already passed the given key because the keys are sorted
            stop = true;
        if (this->elements[current].first == c) {
            values.push_back(this->elements[current].second);
            found = true;
        }
        current = this->nextPosition[current];
    }
    return values;
}
//Best case: Theta(1), Worst case: Theta(capacity) => Total complexity: O(capacity) (best case if the key is the first or it is not in the multimap, worst case if the key is on the last position)

bool SortedMultiMap::remove(TKey c, TValue v) {
	int current = this->head;
	int previous = -1;

    while (current != -1) {
        if (this->elements[current].first == c && this->elements[current].second == v)      // we found the pair that we need to remove
            break;

        previous = current;
        current = this->nextPosition[current];
    }
    if (current != -1) {                    // the pair is in the multimap
        if (current == this->head)                              // if the pair is the head we change the head
            this->head = this->nextPosition[this->head];
        else
            this->nextPosition[previous] = this->nextPosition[current];     // if the pair is not the head we make the previous pair point to the pair after the pair that we remove
        this->nextPosition[current] = this->firstEmpty;                 //make the spot of the removed pair empty
        this->firstEmpty = current;
        this->nrElements--;
        return true;
    }
    else                        // the pair was not found in the multimap
        return false;
}
//Best case: Theta(1), Worst case: Theta(capacity) => Total complexity: O(capacity) (best case if the pair is the first one, worst case if the pair is not in the map)

int SortedMultiMap::size() const {
	return this->nrElements;
}
//Theta(1)

bool SortedMultiMap::isEmpty() const {
    if (this->nrElements == 0)
        return true;
    return false;
}
//Theta(1)

void SortedMultiMap::resize() {
    TElem* resize_elements = new TElem[this->capacity * 2];
    int* resize_nextPosition = new int[this->capacity * 2];
    for (int index = 0; index < this->capacity; index++) {
        resize_elements[index] = this->elements[index];
        resize_nextPosition[index] = this->nextPosition[index];
    }

    for (int index = this->capacity; index < this->capacity * 2 - 1; index++)
        resize_nextPosition[index] = index + 1;

    resize_nextPosition[this->capacity * 2 - 1] = -1;

    firstEmpty = this->capacity;
    this->capacity *= 2;

    delete[] this->elements;
    delete[] this->nextPosition;
    this->elements = resize_elements;
    this->nextPosition = resize_nextPosition;
}
//Theta(newCapacity) (first for loop: newCapacity/2, second for loop: newCapacity/2)

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}
//Theta(1)

SMMValueIterator SortedMultiMap::iterator_value(TKey k) const {
    return SMMValueIterator(*this, k);
}
//Theta(1)

SortedMultiMap::~SortedMultiMap() {
	delete[] this->elements;
	delete[] this->nextPosition;
}
//Theta(1)
