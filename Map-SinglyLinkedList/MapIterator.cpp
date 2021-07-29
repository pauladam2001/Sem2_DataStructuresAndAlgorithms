#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
	this->currentNode = this->map.head;
	this->currentPos = 0;
}
//Theta(1)

void MapIterator::first() {
    if (this->map.head == nullptr)
        throw exception();
	this->currentNode = this->map.head;
	this->currentPos = 0;
}
//Theta(1)

void MapIterator::next() {
    if (map.size() == 0)
        throw exception();
    if (this->valid()) {
        currentNode = currentNode->next;
        this->currentPos++;
    }
    else
        throw exception();
}
//Theta(1)

void MapIterator::jumpBackward(int k) {
    if (k <= 0)
        throw exception();
    int neededPosition = this->currentPos - k;
    if (neededPosition < 0) {
        this->currentNode = nullptr;
    }
    else {
        this->first();
        while (this->currentPos < neededPosition) {
            this->next();
        }
    }
    if (!this->valid())
        throw exception();
}
//O(n)

TElem MapIterator::getCurrent(){
    if (this->valid())
        return currentNode->info;
    else
        throw exception();
	    //return NULL_TELEM;
}
//Theta(1)

bool MapIterator::valid() const {
    if (this->currentNode != nullptr)
        return true;
	return false;
}
//Theta(1)
