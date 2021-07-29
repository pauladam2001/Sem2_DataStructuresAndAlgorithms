#include <exception>
#include "BagIterator.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c) {
    this->currentPositionInHashTable = 0;

    while (this->currentPositionInHashTable < this->bag.m && this->bag.hashTable[this->currentPositionInHashTable] == nullptr)
        this->currentPositionInHashTable++;                 // we search for the first linked list which has elements

    if (this->currentPositionInHashTable < this->bag.m)
        this->currentNodeInLinkedList = this->bag.hashTable[this->currentPositionInHashTable];
    else
        this->currentNodeInLinkedList = nullptr;            // if there are no such lists the iterator becomes invalid
}
//Best case: Theta(1), Worst case: Theta(m) => Total complexity: O(m) (best case when the first available linked list if on the first position, worst case when the first available linked list is on the last position)

void BagIterator::first() {                                     // same with the constructor
    this->currentPositionInHashTable = 0;

    while (this->currentPositionInHashTable < this->bag.m && this->bag.hashTable[this->currentPositionInHashTable] == nullptr)
        this->currentPositionInHashTable += 1;

    if (this->currentPositionInHashTable < this->bag.m)
        this->currentNodeInLinkedList = this->bag.hashTable[this->currentPositionInHashTable];
    else
        this->currentNodeInLinkedList = nullptr;
}
//Best case: Theta(1), Worst case: Theta(m) => Total complexity: O(m) (best case when the first available linked list if on the first position, worst case when the first available linked list is on the last position)

void BagIterator::next() {
    if (this->bag.size() == 0)
        throw exception();
    if (this->valid()) {
        if (this->currentNodeInLinkedList->next != nullptr) {                      // if we still have elements in the linked list we go to the next one
            this->currentNodeInLinkedList = this->currentNodeInLinkedList->next;
        }
        else {                                      // else we go to the next linked list in the hash table
            this->currentPositionInHashTable++;
            while (this->currentPositionInHashTable < this->bag.m && this->bag.hashTable[this->currentPositionInHashTable] == nullptr)
                this->currentPositionInHashTable++;

            if (this->currentPositionInHashTable < this->bag.m)
                this->currentNodeInLinkedList = this->bag.hashTable[this->currentPositionInHashTable];      // we still have non-parsed linked lists
            else
                this->currentNodeInLinkedList = nullptr;        // we parsed all elements of the hash table, so the iterator becomes invalid
        }
    }
    else {
        throw exception();
    }
}
//Best case: Theta(1), Worst case: Theta(m) => Total complexity: O(m) (best case when we still have elements in the current linked list, worst case when we ran out of elements in the current linked list and that linked list is on the first position and there is no other linked list)

bool BagIterator::valid() const {
    return this->currentPositionInHashTable < this->bag.m && this->currentNodeInLinkedList != nullptr;
}
//Theta(1)

TElem BagIterator::getCurrent() const {
    if (this->valid())
        return this->currentNodeInLinkedList->info;
    else
        throw exception();
}
//Theta(1)
