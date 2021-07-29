#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	int currentElement;

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};

class SMMValueIterator{
    friend class SortedMultiMap;
private:
    //DO NOT CHANGE THIS PART
    const SortedMultiMap& map;
    TKey key;
    SMMValueIterator(const SortedMultiMap& map, TKey k);

    int currentElement;
    vector<TValue> values;
    int valuesIndex;

public:
    void first_valueIterator();
    void next_valueIterator();
    bool valid_valueIterator() const;
    TValue getCurrent_valueIterator() const;
};
