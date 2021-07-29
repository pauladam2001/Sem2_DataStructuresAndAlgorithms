#include "ShortTest.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <assert.h>
#include <iostream>

bool relation1(TComp e1, TComp e2) {
	return e1 <= e2;
}

void testAll() {
	SortedBag sb(relation1);
	sb.add(5);
	sb.add(6);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(8);

	assert(sb.size() == 6);
	assert(sb.nrOccurrences(5) == 2);

	assert(sb.remove(5) == true);
	assert(sb.size() == 5);

	assert(sb.search(6) == true);
	assert(sb.isEmpty() == false);


	sb.addOccurrences(3, 11);
	assert(sb.size() == 8);
	assert(sb.search(11) == true);
	assert(sb.nrOccurrences(11) == 3);
	assert(sb.remove(11) == true);
	assert(sb.nrOccurrences(11) == 2);
    assert(sb.remove(11) == true);
	assert(sb.size() == 6);


//	assert(sb.search(0) == true);
//	assert(sb.search(8) == true);

	SortedBagIterator it = sb.iterator();
	assert(it.valid() == true);
//	int count = 0;
	while (it.valid()) {
//		int x = it.getCurrent();
//		std::cout << x << " ";
//        count++;
		it.next();
	}
//	assert(count == sb.size());
	assert(it.valid() == false);
	it.first();
	assert(it.valid() == true);
}
