#include <iostream>
#include "Heap.h"

using namespace std;

int main()
{
	heap* for_test;
	for_test = new heap();
	for_test->insert(5);
	for_test->insert(3);
	for_test->insert(2);
	for_test->insert(4);
	for_test->insert(1);

	Iterator* dftIterator = for_test->create_dft_iterator();

	while (dftIterator->has_next())
		cout << dftIterator->next() << endl;

	return 0;
}