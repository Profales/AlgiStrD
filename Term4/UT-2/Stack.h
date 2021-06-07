#pragma once
#include <stdexcept>
#include <iostream>
using namespace std;
template <class T>
class stack
{
private:
	class st_node
	{
	public:
		st_node(T info, st_node* prev = nullptr, st_node* next = nullptr)
		{
			this->info = info;
			this->prev = prev;
			this->next = next;
		}
		~st_node() {};
		T info;
		st_node* prev;
		st_node* next;
	};
public:
	st_node* top;
	stack()
	{
		top = nullptr;
	}
	void push(T to_push)
	{
		if (top)
		{
			st_node* buf = new st_node(to_push);
			buf->prev = top;
			top->next = buf;
			top = buf;
		}
		else top = new st_node(to_push);
	}
	T pop()
	{
		if (!top)
			throw out_of_range("An error occured.");
		if (top->prev == nullptr)
		{
			T tmp = top->info;
			top = nullptr;
			delete top;
			return tmp;
		}
		else
		{
			st_node node_temp = top;
			T tmp = node_temp->info;
			top = top->prev;
			top->next = nullptr;
			node_temp->prev = nullptr;
			delete node_temp;
			return tmp;
		}
	}
	void print()
	{
		st_node* current = top;
		if (top)
		{
			while (current->prev)
			{
				cout << current->info << " ";
				current = current->prev;
			}
			cout << current->info;
			cout << endl;
		}
		else throw out_of_range("An error occured: stack is empty.");
	}
	T what_at(int index)
	{
		st_node* current = top;
		int i = 0;
		while (i != index)
		{
			if (current->prev)
				current = current->prev;
			else throw "No such element.";
			i++;
		}
		return current->info;
	}
	~stack()
	{
		T tmp;
		while (top)
		{
			tmp = pop();
		}
	}
};
