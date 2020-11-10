#include "LinkedList.h"
#include <iostream>
using namespace std;

int main()
{
	LinkedList* list;
	list = new LinkedList();
	list->push_back(1);
	list->push_back(2);
	list->push_back(3);
	list->print_to_console();
	list->insert(4, 1);
	list->print_to_console();
	return 0;
}