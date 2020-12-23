#pragma once
#include "Node.h"

class queue
{
private:
	class q_node
	{
	public:
		q_node(node* elem, q_node* next = nullptr)
		{
			this->elem = elem;
			this->next = next;
		}
		~q_node() {};
		node* elem;
		q_node* next;
	};
public:
	q_node* first;
	q_node* last;
	queue();
	void push(node* to_push);
	node* pop();
	~queue();
};
