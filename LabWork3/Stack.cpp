#include "Stack.h"
#include <iostream>
#include <stdexcept>
using namespace std;

stack::stack()
{
	top = nullptr;
}

void stack::push(node* to_push)
{
	if (top)
	{
		st_node* buf = top;
		top = new st_node(to_push);
		top->next = buf;
	}
	else top = new st_node(to_push);
}

node* stack::pop()
{
	if (top == nullptr)
		return nullptr;
	node* tmp = top->elem;
	top = top->next;
	return tmp;
}

stack::~stack() 
{
	node* tmp;
	while (top)
	{
		tmp = pop();
	}
}