#include "ExtendedTest.h"
#include "ShortTest.h"

#include "Map.h"

#include <crtdbg.h>
#include <iostream>
using namespace std;


int main() {
	testAll();
	testAllExtended();

    _CrtDumpMemoryLeaks();
	cout << "That's all!" << endl;
	system("pause");
	return 0;
}
