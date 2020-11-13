#pragma once

class LinkedList
{
public:
	LinkedList();
	~LinkedList();

	void push_back(int); // add a new element at the end of list
	void push_front(int); // add a new element as the first element of list
	void push_back_list(LinkedList*); // add a new, second list at the end of first list
	void pop_back(); // delete a last element
	void pop_front(); // delete a first element
	void insert(int, size_t); // add a new element by index (before element, which index we have)
	int at(size_t); // get an info of element by index
	void remove(size_t); // delete an element by index
	size_t get_size(); // get a size of list
	void print_to_console(); // print all elements of list to console
	void clear(); // delete all list
	void set(size_t, int); // swap an element taken by index with given element
	bool isEmpty(); // check an emptiness of list

private:
	class Node
	{
	public:
		Node(int, Node*, Node*);
		~Node();
		int data;
		Node* next;
		Node* prev;
	};
	Node* head;
	Node* tail;
	size_t size;
};
