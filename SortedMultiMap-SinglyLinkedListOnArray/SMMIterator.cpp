#include "SMMIterator.h"
#include "SortedMultiMap.h"


SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	this->currentElement = this->map.head;
}
//Theta(1)

void SMMIterator::first(){
	this->currentElement = this->map.head;
}
//Theta(1)

void SMMIterator::next(){
    if (this->map.size() == 0)
        throw exception();
    if (this->valid())
        this->currentElement = this->map.nextPosition[currentElement];
    else
        throw exception();
}
//Theta(1)

bool SMMIterator::valid() const{
    if (this->currentElement == -1)         // it means that we are at the last element in the map and we don't have any elements left
        return false;
    return true;
}
//Theta(1)

TElem SMMIterator::getCurrent() const{
    if (this->valid())
        return this->map.elements[this->currentElement];
    else
        throw exception();
	    //return NULL_TELEM;
}
//Theta(1)




SMMValueIterator::SMMValueIterator(const SortedMultiMap& d, TKey k) : map(d), key(k){
    this->values = this->map.search(this->key);
    this->currentElement = this->values[0];
    this->valuesIndex = 0;
}
//O(capacity)

void SMMValueIterator::first_valueIterator(){
    this->currentElement = this->values[0];
    this->valuesIndex = 0;
}
//Theta(1)

void SMMValueIterator::next_valueIterator(){
    if (this->valuesIndex == this->values.size())
        throw exception();
    if (this->valid_valueIterator()) {
        this->valuesIndex++;
        this->currentElement = this->values[valuesIndex];
    }
    else
        throw exception();
}
//Theta(1)

bool SMMValueIterator::valid_valueIterator() const{
    if (this->valuesIndex == this->values.size())
        return false;
    return true;
}
//Theta(1)

TValue SMMValueIterator::getCurrent_valueIterator() const{
    if (this->valid_valueIterator())
        return this->currentElement;
    else
        throw exception();
    //return NULL_TELEM;
}
//Theta(1)
