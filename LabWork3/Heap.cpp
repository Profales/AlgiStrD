#include "Heap.h"
#include <iostream>
#include <stdexcept>

using namespace std;

node::node()
{
	left_son = nullptr;
	right_son = nullptr;
	parent = nullptr;
	key = 0;
}

heap::heap()
{
	root = nullptr;
	size = 0;
}

bool heap::bftIterator::has_next()
{
	return (current->first != nullptr);
}

int heap::bftIterator::next()
{
	node* tmp;
	tmp = current->pop();
	if (tmp->left_son != nullptr)
		current->push(tmp->left_son);
	if (tmp->right_son != nullptr)
		current->push(tmp->right_son);
	return tmp->key;
}

bool heap::dftIterator::has_next()
{
	return (current->top != nullptr);
}

int heap::dftIterator::next()
{
	node* tmp = cur_heap;
	
	if (tmp->right_son != nullptr)
		current->push(tmp->right_son);
	if (tmp->left_son != nullptr)
		cur_heap = cur_heap->left_son;
	else
		cur_heap = current->pop();
	return tmp->key;
}

heap::bftIterator::bftIterator(node* start)
{
	current = new queue();
	current->push(start);
}

heap::dftIterator::dftIterator(node* start)
{
	current = new stack();
	cur_heap = start;
	current->push(start);
}

Iterator* heap::create_bft_iterator()
{
	return new bftIterator(root);
}

Iterator* heap::create_dft_iterator()
{
	return new dftIterator(root);
}

void heap::heapify(node* current)
{
	if ((current->parent != nullptr) && (current->key > current->parent->key))
	{
		swap(current->key, current->parent->key);
		heapify(current->parent);
	}
	else 
		if ((current->left_son != nullptr) && (current->key < current->left_son->key))
	{
		swap(current->key, current->left_son->key);
		heapify(current->left_son);
	}
	else 
		if ((current->right_son != nullptr) && (current->key < current->right_son->key))
	{
		swap(current->key, current->right_son->key);
		heapify(current->right_son);
	}
}

int find_number_of_edges(int number)
{
	int power = 1;
	int edges = 0;
	while (1)
	{
		if ((number < power * 2) && (number >= power))
		{
			break;
		}
		power *= 2;
		edges++;
	}
	return edges;
}

void heap::insert(int key)
{
	if (root == nullptr)
	{
		root = new node;
		root->key = key;
		size++;
	}
	else
	{
		bool* navigation;
		int new_place = size + 1, i=0;
		int edges = find_number_of_edges(new_place);
		navigation = new bool[edges];
		
		while (new_place != 1)
		{
			if (new_place % 2 == 1)
			{
				new_place = (new_place - 1) / 2;
				navigation[edges - 1 - i] = 0;
			}
			else
			{
				new_place = new_place/ 2;
				navigation[edges - 1 - i] = 1;
			}
			i++;
		}
		node* current = root;
		node* new_node = new node;
		new_node->key = key;
		i = 0;
		if (edges >= 2)
			while (i <= edges - 2)
			{
				if (navigation[i] == 0)
					current = current->right_son;
				else
					current = current->left_son;
				i++;
			}
		if (navigation[i] == 0)
			current->right_son = new_node;
		else
			current->left_son = new_node;
		new_node->parent = current;
		delete []navigation;
		size++;

		heapify(new_node);
	}
}

bool find_number(node* vertice, int key)
{
	if (vertice->key < key)
		return 0;
	if (vertice->key == key)
		return 1;
	else
	{
		if ((vertice->left_son != nullptr)&&(vertice->right_son != nullptr))
			return (find_number(vertice->left_son, key) || find_number(vertice->right_son, key));
		if ((vertice->left_son != nullptr) && (vertice->right_son == nullptr))
			return find_number(vertice->left_son, key);
		else return 0;
	}
}

node* find_node(node* vertice, int key)
{
	if (vertice->key < key)
		return nullptr;
	if (vertice->key == key)
		return vertice;
	else
	{
		if (vertice->left_son != nullptr)
			return find_node(vertice->left_son, key);
		if (vertice->right_son != nullptr)
			return find_node(vertice->right_son, key);
		else return nullptr;
	}
}

bool heap::contains(int key)
{
	return find_number(root, key);
}

void heap::remove(int key)
{
	if ((size == 1)&&(root->key == key))
	{
		root->key = 0;
		delete root;
		size--;
	}
	else if (contains(key) == 1)
	{
		node* current = find_node(root, key);
		bool* navigation;
		int last_place = size, i = 0;
		int edges = find_number_of_edges(last_place);
		navigation = new bool[edges];

		while (last_place != 1)
		{
			if (last_place % 2 == 1)
			{
				last_place = (last_place - 1) / 2;
				navigation[edges - 1 - i] = 0;
			}
			else
			{
				last_place = last_place / 2;
				navigation[edges - 1 - i] = 1;
			}
			i++;
		}
		node* to_delete = root;
		i = 0;
		if (edges >= 1)
			while (i <= edges - 1)
			{
				if (navigation[i] == 0)
					to_delete = to_delete->right_son;
				else
					to_delete = to_delete->left_son;
				i++;
			}
		
		swap(to_delete->key, current->key);

		if (navigation[i] == 1)
			to_delete->parent->left_son = nullptr;
		else 
			to_delete->parent->right_son = nullptr;

		to_delete->parent = nullptr;
		to_delete->key = 0;
		delete to_delete;
		delete[]navigation;
		size--;

		heapify(current);
	}
}

size_t heap::give_size()
{
	return size;
}

heap::~heap()
{ }