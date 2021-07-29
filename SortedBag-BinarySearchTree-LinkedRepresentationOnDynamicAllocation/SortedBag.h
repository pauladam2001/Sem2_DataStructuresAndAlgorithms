#pragma once
//DO NOT INCLUDE SORTEDBAGITERATOR

//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);

class SortedBagIterator;

struct BSTNode {
    TElem info;
    BSTNode* leftChild;
    BSTNode* rightChild;
};

struct stackStruct {
    int index = -1;
    BSTNode **data{};
};

class SortedBag {
	friend class SortedBagIterator;

private:
	BSTNode* root;
	Relation relation;
	int nrOfElems;
    stackStruct stack;

	static BSTNode* get_maximum(BSTNode* node);

public:
	//constructor
	explicit SortedBag(Relation r);

	//adds an element to the sorted bag
	void add(TComp e);

	//removes one occurrence of an element from a sorted bag
	//returns true if an element was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	//checks if an element appears is the sorted bag
	bool search(TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	int size() const;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator() const;

	//checks if the sorted bag is empty
	bool isEmpty() const;

    //adds nr occurrences of elem into the SortedBag (if elem was not in the bag, it will be added).
    //throws an exception if nr is negative
    void addOccurrences(int nr, TComp elem);

	//destructor
	~SortedBag();
};
