#pragma once
#include <string>
using namespace std;
class node
{
public:
	node(int priority = -1, string character="@", node* next = nullptr, node* prev = nullptr)
	{
		this->priority = priority;
		this->character = character;
		this->next = next;
		this->prev = prev;
	};
	~node() {};
	int priority;
	string character;
	node* next;
	node* prev;
};