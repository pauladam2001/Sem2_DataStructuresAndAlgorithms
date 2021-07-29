#pragma once
#include "Map.h"
class MapIterator
{
	//DO NOT CHANGE THIS PART
	friend class Map;
private:
	const Map& map;
	Node* currentNode;
	int currentPos;     //used for jumBackward()

	MapIterator(const Map& m);
public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;

    //moves the current element from the iterator k steps backward, or makes the iterator invalid if there are less than k elements
    // left until the beginning of the Map.
    //throws an exception if the iterator is invalid or k is zero or negative
    void jumpBackward(int k);

};
