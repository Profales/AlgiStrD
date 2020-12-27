#pragma once
#include "Node.h"
class Prefix
{
public:
	Prefix();
	~Prefix();
	void push_back(int priority, string data);
	void push_back(int priority, char data);
	void clear();
	void pop_back();
	node* head;
	node* tail;
};