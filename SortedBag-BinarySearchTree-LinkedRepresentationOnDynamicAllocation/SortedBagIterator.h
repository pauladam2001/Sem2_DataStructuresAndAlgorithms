#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	explicit SortedBagIterator(const SortedBag& b);

    BSTNode* currentNode;
    stackStruct stack;

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};
