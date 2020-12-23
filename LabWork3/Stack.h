#pragma once
#include "Node.h"

class stack
{
private:
	class st_node
	{
	public:
		st_node(node* elem, st_node* next = nullptr)
		{
			this->elem = elem;
			this->next = next;
		}
		~st_node() {};
		node* elem;
		st_node* next;
	};
public:
	st_node* top;
	stack();
	void push(node* to_push);
	node* pop();
	~stack();
};
