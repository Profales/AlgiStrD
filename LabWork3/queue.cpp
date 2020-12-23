#include "queue.h"
#include <iostream>
using namespace std;

queue::queue()
{
	first = nullptr;
	last = nullptr;
}

void queue::push(node* to_push)
{
	if (last == nullptr)
	{
		first = new q_node(to_push);
		last = first;
	}
	else
	{
		last->next = new q_node(to_push);
		last = last->next;
	}
}

node* queue::pop()
{
	node* tmp;
	if (first!=nullptr)
		if (first == last)
		{
			tmp = first->elem;
			first = nullptr;
			last = nullptr;
			return tmp;
		}
		else
		{
			q_node* to_del = first;
			tmp = first->elem;
			first = first->next;
			delete to_del;
			return tmp;
		}
	return nullptr;
}

queue::~queue()
{
	while (first)
	{
		q_node* tmp = first;
		first = first->next;
		delete tmp;
	}
}