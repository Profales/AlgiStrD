#include "Prefix.h"
#include <stdexcept>

using namespace std;

void Prefix::push_back(int priority, string data)
{
	if (head == nullptr)
	{
		head = new node(priority, data, nullptr, nullptr);
		tail = head;
	}
	else
	{
		tail->next = new node(priority, data, nullptr, nullptr);
		tail->next->prev = tail;
		tail = tail->next;
	}
}

void Prefix::push_back(int priority, char data)
{
	string default_string;
	default_string.push_back(data);
	if (head == nullptr)
	{
		head = new node(priority, default_string, nullptr, nullptr);
		tail = head;
	}
	else
	{
		tail->next = new node(priority, default_string, nullptr, nullptr);
		tail->next->prev = tail;
		tail = tail->next;
	}
}

void Prefix::pop_back()
{
	if (head == tail)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		tail = tail->prev;
		delete tail->next;
		tail->next = nullptr;
	}
}


void Prefix::clear() 
{
	while (head != nullptr) 
	{
		pop_back();
	}
}

Prefix::~Prefix()
{
	clear();
}
