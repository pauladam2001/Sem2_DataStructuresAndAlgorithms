#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)              //TODO check if the size of the bag is 0
{
	this->current = 0;                                          // the current index in the array of elements
	this->frequency = this->bag.frequency[this->current];       // the frequency of the number at the current index
}
//Theta(1)

void BagIterator::first() {
	this->current = 0;
	this->frequency = this->bag.frequency[this->current];
}
//Theta(1)

void BagIterator::next() {                              //TODO check if the size of the bag is 0
    if (this->valid()) {
        if (this->frequency == 1) {
            this->current++;                                        // if the frequency is 1 we move to the next element in the array
            this->frequency = this->bag.frequency[this->current];
        }
        else {
            this->frequency--;                                      // if the frequency is > 1 we decrease the frequency
        }
    }
    else {
	    throw exception();
	}
}
//Theta(1)

void BagIterator::previous() {              //TODO check if the size of the bag is 0
    int sem = 0;
    if (this->current == 0 && this->frequency == this->bag.frequency[this->current]) {      // this means that we are at the first element
        this->current = this->bag.currentNr;
        sem = 1;
    }
    else {
        if (this->frequency == this->bag.frequency[this->current]) {
            this->current--;
        }
        else {
            this->frequency++;
        }
    }
    if (this->valid() == false && sem == 1)     //if we are at the first position, with the first
        throw exception();                       //if we make this->current = the last position
}                                                //such that the valid function will return false
//Theta(1)

bool BagIterator::valid() const {
    if (this->current == this->bag.currentNr) {     //if there are no more elements (we are at the end of the array), then we return false
        return false;
    }
    else {
        return true;
    }
}
//Theta(1)

TElem BagIterator::getCurrent() const
{
    if (this->valid()) {
        return this->bag.elements[this->current];
    }
    else {
        //return NULL_TELEM
        throw exception();
    }
}
//Theta(1)
