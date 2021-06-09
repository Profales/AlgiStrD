#pragma once
#include <stdexcept>
#include <iostream>
using namespace std;
template <class T>
class ListL2
{
private:
	class lst_node
	{
	public:
		lst_node(T info, lst_node* next = nullptr, lst_node* prev = nullptr)
		{
			this->info = info;
			this->next = next;
			this->prev = prev;
		}
		lst_node()
		{
			this->prev = nullptr;
			this->next = nullptr;
		}
		~lst_node() {};
		T info;
		lst_node* prev;
		lst_node* next;
	};
public:
	lst_node* top;
	lst_node* tail;
	size_t size;
	ListL2()
	{
		top = nullptr;
		tail = nullptr;
		size = 0;
	}
	void push_back(T data)
	{
		if (isEmpty())
		{
			top = tail = new lst_node(data);
		}
		else
		{
			lst_node* temp = new lst_node(data, nullptr, tail);
			tail->next = temp;
			tail = temp;
		}
		size++;
	}

	void push_front(T data)
	{
		if (!isEmpty())
		{
			lst_node* cur = top;
			top = new lst_node(data, top);
			cur->prev = top;
		}
		else
		{
			top = tail = new lst_node(data, nullptr, nullptr);
		}
		size++;
	}
	T pop_front()
	{
		if (!top)
			throw out_of_range("An error occured.");
		if (top->next == nullptr)
		{
			T tmp = top->info;
			tail = nullptr;
			top = nullptr;
			delete top;
			delete tail;
			size--;
			return tmp;
		}
		else
		{
			lst_node* node_temp = top;
			T tmp = node_temp->info;
			top = top->next;
			top->prev = nullptr;
			node_temp->next = nullptr;
			delete node_temp;
			size--;
			return tmp;
		}
	}
	T pop_back()
	{
		if (!tail)
			throw out_of_range("An error occured.");
		if (tail->prev == nullptr)
		{
			T tmp = tail->info;
			tail = nullptr;
			top = nullptr;
			delete top;
			delete tail;
			size--;
			return tmp;
		}
		else
		{
			lst_node* node_temp = tail;
			T tmp = node_temp->info;
			tail = tail->prev;
			tail->next = nullptr;
			node_temp->prev = nullptr;
			delete node_temp;
			size--;
			return tmp;
		}
	}
	void print()
	{
		lst_node* current = top;
		if (top)
		{
			while (current->next)
			{
				cout << current->info << " ";
				current = current->next;
			}
			cout << current->info;
			cout << endl;
		}
		else throw out_of_range("An error occured: list is empty.");
	}
	T what_at(int index)
	{
		if (top)
		{
			lst_node* current = top;
			int i = 0;
			while (i != index)
			{
				if (current->next)
					current = current->next;
				else
					if (i == index)
						return current->info;
				i++;
			}
			return current->info;
		}
		else throw "An error occured.";

	}
	int FindAnElement(T dataToFind)
	{
		int i = 0;
		if (top != nullptr) 
		{
			lst_node* current = top;
			while(current)
			{
				if (dataToFind == current->info) 
				{
					return i;
				}
				current = current->next;
				i++;
			}
		}
		return -1;
	}
	size_t give_size()
	{
		return size;
	}
	~ListL2()
	{
		T tmp;
		while (top)
		{
			tmp = pop_front();
		}
	}
	lst_node* give_top()
	{
		return top;
	}
	bool isEmpty()
	{
		return (top == nullptr);
	}
};
