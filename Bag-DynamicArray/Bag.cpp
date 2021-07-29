#include "Bag.h"
#include "BagIterator.h"
#include <exception>
using namespace std;


Bag::Bag() {
    this->capacity = 100;
	this->elements = new TElem[this->capacity];
	this->frequency = new TElem[this->capacity];
	this->nrElem = 0;
	this->currentNr = 0;
}
//Theta(1)

//If I try to make a copy constructor: "Definition of implicitly declared copy constructor"

void Bag::add(TElem elem) {
    int index = 0;
    bool done = false;
    if (this->currentNr == this->capacity) {        // if the array is full we need to increase its capacity
        this->resize();
    }
    while (index < this->currentNr && !done) {
        if (this->elements[index] == elem) {
            this->frequency[index]++;               // if elem is already in the array we increase the frequency
            this->nrElem++;
            done = true;
        }
        else {
            index++;
        }
    }
    if (index == this->currentNr) {
        this->elements[this->currentNr] = elem;
        this->frequency[this->currentNr] = 1;       // here if elem is not in the array yet
        this->nrElem++;
        this->currentNr++;
    }
}
//Best case: Theta(1), Worst case: Theta(currentNr) => Total complexity: O(currentNr)

bool Bag::remove(TElem elem) {
	int index = 0;
	bool found = false;
    while (index < this->currentNr && !found) {
        if (this->elements[index] == elem) {
            found = true;
        }
        else {
            index++;
        }
    }
    if (!found) {
        return false;
    }
    else {
        if (this->frequency[index] > 1) {
            this->frequency[index]--;           // if the frequency is bigger than 1 we decrease it by 1
            this->nrElem--;
        }
        else if (this->frequency[index] == 1) {
            this->elements[index] = this->elements[this->currentNr - 1];
            this->frequency[index] = this->frequency[this->currentNr - 1];      // if the frequency is 1 we remove the element from the array
            this->nrElem--;
            this->currentNr--;
        }
        return true;
    }
}
//Best case: Theta(1), Worst case: Theta(currentNr) => Total complexity: O(currentNr)

bool Bag::search(TElem elem) const {
	int index = 0;
    while (index < this->currentNr) {
        if (this->elements[index] == elem) {
            return true;
        }
        index++;
    }
	return false; 
}
//Best case: Theta(1), Worst case: Theta(currentNr) => Total complexity: O(currentNr)

int Bag::nrOccurrences(TElem elem) const {
	int index = 0;
    while (index < this->currentNr) {
        if (this->elements[index] == elem) {
            return this->frequency[index];
        }
        index ++;
    }
	return 0; 
}
//Best case: Theta(1), Worst case: Theta(currentNr) => Total complexity: O(currentNr)

int Bag::size() const {
	return this->nrElem;
}
//Theta(1)

bool Bag::isEmpty() const {
    if (this->nrElem == 0) {
        return true;
    }
    else {
        return false;
    }
}
//Theta(1)

void Bag::resize() {
    TElem* resize_array = new TElem[this->capacity * 2];
    TElem* resize_array_frequency = new TElem[this->capacity * 2];
    for (int index = 0; index < this->capacity; index++) {
        resize_array[index] = this->elements[index];
        resize_array_frequency[index] = this->frequency[index];                 // we double the capacity
    }

    this->capacity *= 2;
    delete[] this->elements;
    delete[] this->frequency;
    this->elements = resize_array;
    this->frequency = resize_array_frequency;
}
//Theta(newCapacity)

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}
//Theta(1)

Bag::~Bag() {
	delete[] this->elements;
	delete[] this->frequency;
}
//Theta(1)
