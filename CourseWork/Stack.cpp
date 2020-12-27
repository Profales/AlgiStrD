#include "Stack.h"
#include <iostream>
using namespace std;

stack::stack()
{
	top = new st_node();
}

void stack::push(string data, int priority) 
{
	top = new st_node(data, priority, top);
}

void stack::push(char new_elem, int priority) 
{
	string insert;
	insert.push_back(new_elem);
	top = new st_node(insert, priority, top);
}

node* stack::pop()
{
	if (top == nullptr)
		return nullptr;
	node* tmp = top->elem;
	top = top->next;
	return tmp;
}

void stack::print_to_console()
{
	st_node* current;
	current = top;
	while (current)
	{
		cout << current->elem->character << ' ';
		current = current->next;
	}
	cout << endl;
}

stack::~stack()
{
	node* tmp;
	while (top)
	{
		tmp = pop();
	}
}
