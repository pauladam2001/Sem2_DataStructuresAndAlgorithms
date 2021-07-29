#include "Bag.h"
#include "BagIterator.h"
#include <exception>
using namespace std;


Bag::Bag() {
    this->m = 11;
    this->loadFactor = 0.7;
    this->nrOfElements = 0;

	this->hashTable = new Node*[this->m];   // initial hash table size

	for (int index = 0; index < this->m; index++)       // initializing the heads of the singly linked lists with nullptr
	    this->hashTable[index] = nullptr;
}
//Theta(m)

void Bag::add(TElem elem) {
	int positionInHashTable = this->hash_function(elem);

    Node* newNode = new Node;
    newNode->info = elem;
    newNode->next = this->hashTable[positionInHashTable];           // add at beginning
    this->hashTable[positionInHashTable] = newNode;
    this->nrOfElements++;

    if ((double)(this->nrOfElements / this->m) > this->loadFactor)      // if the actual load factor is bigger than this->loadFactor we need resize
        this->resize_hash_table();
}
//Theta(1) (sometimes we also need to resize the hash table)

bool Bag::remove(TElem elem) {
	int positionInHashTable = this->hash_function(elem);

    if (this->hashTable[positionInHashTable] == nullptr)            // if the linked list for the position is null it means that the element is not in the bag
        return false;

    if (this->hashTable[positionInHashTable]->info == elem) {           // if the element is the head
        Node* nextNode = this->hashTable[positionInHashTable]->next;
        delete this->hashTable[positionInHashTable];
        this->hashTable[positionInHashTable] = nextNode;
        this->nrOfElements--;
        return true;
    }

    Node* currentNode = this->hashTable[positionInHashTable];
    Node* previousNode = nullptr;
    while (currentNode != nullptr && currentNode->info != elem) {       // if the elements is not the head we search for it
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode == nullptr)             // the element is not in the bag
        return false;

    previousNode->next = currentNode->next;         // we found the element somewhere
    delete currentNode;
    this->nrOfElements--;
    return true;
}
//Best case: Theta(1), Worst case: Theta(nrOfElements) => Total complexity: O(nrOfElements) (best case when the element is the first in the linked list, worst case when all elements of the bag are in the same linked list)

bool Bag::search(TElem elem) const {
	int positionInHashTable = this->hash_function(elem);

    if (this->hashTable[positionInHashTable] == nullptr)       // if the linked list for the position is null it means that the element is not in the bag
        return false;

    Node* currentNode = this->hashTable[positionInHashTable];
    while (currentNode != nullptr && currentNode->info != elem)         // we search for the element
        currentNode = currentNode->next;

    if (currentNode == nullptr)         // the element is not in the bag
        return false;
    else
        return true;                    // we found the element
}
//Best case: Theta(1), Worst case: Theta(nrOfElements) => Total complexity: O(nrOfElements) (best case when the element is the first in the linked list, worst case when all elements of the bag are in the same linked list)

int Bag::nrOccurrences(TElem elem) const {
	int counter = 0;
    int positionInHashTable = this->hash_function(elem);

    Node* currentNode = this->hashTable[positionInHashTable];
    while (currentNode != nullptr) {            // we parse the linked list associated to the position in the hash table were the element should be found
        if (currentNode->info == elem)
            counter++;
        currentNode = currentNode->next;
    }

    return counter;             // return the number of occurrences
}
//Best case: Theta(1), Worst case: Theta(nrOfElements) => Total complexity: O(nrOfElements) (best case when the linked list associated to the element doesn't exist, worst case when we parse the linked list)

int Bag::size() const {
	return this->nrOfElements;
}
//Theta(1)

bool Bag::isEmpty() const {
	return this->nrOfElements == 0;
}
//Theta(1)

int Bag::hash_function(int elem) const {                // we use the division method
    if (elem < 0)
        elem = -elem;

    return elem % this->m;
}
//Theta(1)

void Bag::resize_hash_table() {
    Node** auxHashTable = new Node*[this->m * 2];
    Node* currentNode;
    int newPositionInHashTable;

    this->m *= 2;   // multiply the size of the hash table with 2

    for (int index = 0; index < this->m; index++)       // initializing the heads of the singly linked lists with nullptr
        auxHashTable[index] = nullptr;

    for(int index = 0; index < this->m / 2; index++) {      // parse the old hash table
        currentNode = this->hashTable[index];
        while (currentNode != nullptr) {
            newPositionInHashTable = this->hash_function(currentNode->info);    // compute the new positions of the elements in the resized hash table

            Node* newNode = new Node;
            newNode->info = currentNode->info;
            newNode->next = auxHashTable[newPositionInHashTable];           // store the elements on the new positions in the resized hash table
            auxHashTable[newPositionInHashTable] = newNode;

            currentNode = currentNode->next;
        }
    }

    for (int index = 0; index < this->m / 2; index++) {
        Node* auxNode;
        while (this->hashTable[index] != nullptr) {             // same with the destructor
            auxNode = this->hashTable[index]->next;
            delete this->hashTable[index];
            this->hashTable[index] = auxNode;
        }
    }

    this->hashTable = auxHashTable;
}
//Theta(new m)

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}
//Best case:Theta(1), Worst case:Theta(m) => Total complexity: O(m) (best case when the first available linked list if on the first position, worst case when the first available linked list is on the last position)

int Bag::removeElementsWithMultipleOccurrences() {
    Node* currentNode;
    int ct = 0;
    for (int index = 0; index < this->m; index++) {
        currentNode = this->hashTable[index];
        while (currentNode != nullptr) {
            int nrOfOccurences = this->nrOccurrences(currentNode->info);
            if (nrOfOccurences > 1) {
                while (nrOfOccurences > 0) {
                    this->remove(currentNode->info);
                    nrOfOccurences--;
                    ct++;
                }
            }
            currentNode = currentNode->next;
        }
    }
    return ct;
}
//Theta(m * nrOfElements^2 * nrOfOccurences)

Bag::~Bag() {
	for (int index = 0; index < this->m; index++) {
	    Node* auxNode;
	    while (this->hashTable[index] != nullptr) {
            auxNode = this->hashTable[index]->next;         // deallocate the singly linked lists and the hash table
            delete this->hashTable[index];
            this->hashTable[index] = auxNode;
        }
	}
	delete[] this->hashTable;
}
//Theta(nrOfElements)
