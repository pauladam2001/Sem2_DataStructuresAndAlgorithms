#include "ShortTest.h"
#include <assert.h>
#include "Bag.h"
#include "BagIterator.h"


void testAll() { 
	Bag b;
	assert(b.isEmpty() == true);
	assert(b.size() == 0); 
	b.add(5);
	b.add(1);
	b.add(10);
	b.add(7);
	b.add(1);
	b.add(11);
	b.add(-3);
	assert(b.size() == 7);
	assert(b.search(10) == true);
	assert(b.search(16) == false);
	assert(b.nrOccurrences(1) == 2);
	assert(b.nrOccurrences(7) == 1);
	assert(b.remove(1) == true);
	assert(b.remove(6) == false);
	assert(b.size() == 6);
	assert(b.nrOccurrences(1) == 1);
	BagIterator it = b.iterator();
	it.first();
	while (it.valid()) {
		TElem e = it.getCurrent();
		it.next();
	}

	Bag b1;
    assert(b1.isEmpty() == true);
    assert(b1.size() == 0);
    b1.add(5);
    b1.add(1);
    b1.add(10);
    b1.add(7);
    b1.add(1);
    b1.add(11);
    b1.add(-3);
    b1.add(5);
    b1.add(5);
    b1.add(10);
    b1.add(11);
    b1.add(5);
    assert(b1.removeElementsWithMultipleOccurrences() == 10);

    Bag b2;
    assert(b2.isEmpty() == true);
    assert(b2.size() == 0);
    b2.add(1);
    b2.add(2);
    b2.add(3);
    b2.add(-3);
    b2.add(-3);
    b2.add(4);
    b2.add(5);
    b2.add(1);
    b2.add(6);
    b2.add(7);
    b2.add(8);
    b2.add(8);
    assert(b2.removeElementsWithMultipleOccurrences() == 6);
}
