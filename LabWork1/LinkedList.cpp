#include <iostream>
#include "LinkedList.h"
#include <stdexcept>

using namespace std;

LinkedList::Node::Node(int data, Node* next = nullptr, Node* prev = nullptr)
{
	this->data = data;
	this->next = next;
	this->prev = prev;
};

LinkedList::Node::~Node()
{
	next = nullptr;
	prev = nullptr;
};

LinkedList::LinkedList()
{
	head = nullptr;
	tail = nullptr;
	current = nullptr;
	size = 0;
}

bool LinkedList::isEmpty()
{
	return (head == nullptr);
}

void LinkedList::push_back(int newElem)
{
	if (isEmpty())
	{
		head = new Node(newElem);
		tail = head;
		current = head;
		size++;
	}
	else
	{
		tail->next = new Node(newElem);
		tail->next->prev = tail;
		tail = tail->next;
		size++;
	}
}

void LinkedList::push_front(int newElem)
{
	if (isEmpty())
	{
		head = new Node(newElem);
		tail = head;
		current = head;
		size++;
	}
	else
	{
		head->prev = new Node(newElem);
		head->prev->next = head;
		head = head->prev;
		size++;
	}
}

void LinkedList::pop_back()
{
	if (size == 0)
		return;
	if (size == 1)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
		current = nullptr;
		size = 0;
	}
	else
	{
		tail = tail->prev;
		delete tail->next;
		tail->next = nullptr;
		size--;
	}
}

void LinkedList::pop_front()
{
	if (size == 0)
		return;
	if (size == 1)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
		current = nullptr;
		size = 0;
	}
	else
	{
		head = head->next;
		delete head->prev;
		head->prev = nullptr;
		size--;
	}
}

void LinkedList::insert(int newElem, size_t index)
{
	if (index >= size)
	{
		throw out_of_range("This index is greater than size of that list.");
	}
	size_t counter = 0;
	current = head;
	while (counter != index)
	{
		current = current->next;
		counter++;
	}
	Node* temp = new Node(newElem);
	temp->prev = current->prev;
	current->prev->next = temp;
	temp->next = current;
	current->prev = temp;
	size++;
}

int LinkedList::at(size_t index)
{
	if (index >= size)
	{
		throw out_of_range("This index is greater than size of that list.");
	}
	else 
	{
		size_t counter = 0;
		current = head;
		while (counter != index) 
		{
			current = current->next;
			counter++;
		}
		return current->data;
	}
}

void LinkedList::remove(size_t index)
{
	if (index >= size)
	{
		throw out_of_range("This index is greater than size of that list.");
	}
	if (index == 0)
		pop_front();
	if (index == size - 1)
		pop_back();
	else
	{
		size_t counter = 0;
		current = head;
		while (counter != index) 
		{
			current = current->next;
			counter++;
		}
		current->next->prev = current->prev;
		current->prev->next = current->next;
		size--;
		delete current;
		current = nullptr;
	}
}

size_t LinkedList::get_size()
{
	return size;
}

void LinkedList::print_to_console()
{
	if (size == 0)
	{
		throw out_of_range("Nothing to print: list is empty");
	}
	else
	{
		current = head;
		while (current != nullptr)
		{
			cout << current->data << ' ';
			current = current->next;
		}
		cout << endl;
	}
}

void LinkedList::clear()
{
	while (head!=nullptr)
	{
		pop_front();
	}
}

void LinkedList::set(size_t index, int newElem)
{
	if (index >= size)
	{
		throw out_of_range("This index is greater than size of that list.");
	}
	else 
	{
		size_t counter = 0;
		current = head;
		while (counter != index)
		{
			current = current->next;
			counter++;
		}
		current->data = newElem;
	}
}

void LinkedList::push_back_list(LinkedList* secondList)
{
	if (secondList->size == 0)
	{
		throw out_of_range("Nothing to add: the second list is empty.");
	}
	else
	{
		if (size == 0)
		{
			throw out_of_range("The first list is empty.");
		}
		else
		{
			size_t counter = 0;
			current = secondList->head;
			while (counter < secondList->size)
			{
				push_back(current->data);
				current = current->next;
				counter++;
			}
		}
	}
}

LinkedList::~LinkedList()
{
	clear();
};