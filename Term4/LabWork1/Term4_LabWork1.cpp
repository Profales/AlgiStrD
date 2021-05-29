#include <iostream>
#include "Map.h"
using namespace std;
int main()
{
	setlocale(LC_ALL, "Rus");
	cout << "Привет!" << endl;
	map<int, char> RBtree;
	stack<int>* keys_list;
	stack<char>* values_list;
	int keys[3] = { 1, 2, 3 /*9, 10, 11, 1, 3*/ };
	char values[3] = { 'a', 'b', 'c' /*, 'd', 'e'*/};
	for (size_t i = 0; i < 3; i++)
		RBtree.insert(keys[i], values[i]);
	RBtree.print();
	//RBtree.remove(9);
	//RBtree.remove(12);
	RBtree.print();

	keys_list = RBtree.get_keys();
	values_list = RBtree.get_values();
	
	cout << "Список ключей дерева: ";
	keys_list->print();
	cout << "Список информации дерева: ";
	values_list->print();
	cout << "Пока!" << endl;
}

