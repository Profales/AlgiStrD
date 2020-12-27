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
		st_node(string character = "@", int priority = -1, st_node* next = nullptr)
		{
			this->elem = new node(priority, character, nullptr, nullptr);
			this->next = next;
		}
		~st_node() {};
		node* elem;
		st_node* next;
	};
public:
	st_node* top;
	stack();
	void push(string character, int priority);
	void push(char character, int priority);
	void print_to_console();
	node* pop();
	~stack();
};
