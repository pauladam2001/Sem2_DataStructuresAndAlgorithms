#pragma once
//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111;
typedef int TElem;
class BagIterator;

struct Node {
    TElem info{};
    Node* next{};
};

class Bag {

private:
	int m;  // hash table size
	int nrOfElements;
	double loadFactor;
    Node** hashTable;

    int hash_function(int elem) const;

    void resize_hash_table();

	//DO NOT CHANGE THIS PART
	friend class BagIterator;
public:
	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appearch is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

    //removes completely all elements that appear multiple times in the Bag (all their occurrences are removed)
    //returns the number of removed elements
    int removeElementsWithMultipleOccurrences();


    //destructor
	~Bag();
};
