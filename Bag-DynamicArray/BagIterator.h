#include "Bag.h"

class BagIterator
{
	//DO NOT CHANGE THIS PART
	friend class Bag;
	
private:
	const Bag& bag;
	int current;
	int frequency;

	BagIterator(const Bag& c);
public:
	void first();
	void next();

    //changes the current element from the iterator to the previous element, or, if the current element was the first, makes the iterator invalid
    //throws an exception if the iterator is not valid
    void previous();
	TElem getCurrent() const;
	bool valid() const;
};
