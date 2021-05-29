#pragma once
//#include "Iterator.h"
#include "Stack.h"
#include <iostream>
#include <stdexcept>
using namespace std;
enum ColorName
{
	BLACK,
	RED
};
template <typename key_t, typename value_t>
class map
{
private:
	class Node
	{
	public:
		key_t key;
		value_t value;
		ColorName color;
		Node* left;
		Node* right;
		Node* parent;

		Node(key_t key, value_t value, ColorName color, Node* left, Node* right, Node* parent)
		{
			this->key = key;
			this->value = value;
			this->color = color;
			this->left = left;
			this->right = right;
			this->parent = parent;
		}
		/*Node()
		{
			this->key = nullptr;
			this->value = nullptr;
			this->color = BLACK;
			this->left = nullptr;
			this->right = nullptr;
			this->parent = nullptr;
		}*/
		~Node() {}
	};
private:
	Node* root;
	Node* nil;
	size_t size; // it is necessary to remember size (number of nodes) of tree to make "get_keys()" and "get_values()" with iterator correctly

	// some helper methods
	void rightRotate(Node* curX)
	{
		Node* curY = curX->left;		// Y is a left son for X!
		curX->left = curY->right;
		if (curY->right != nil)		// if right son of Y exists
			curY->right->parent = curX;
		if (curY != nil)
			curY->parent = curX->parent;		// parent of x is a parent of y
		if (curX->parent == nil)	// no parent for X
			root = curY;		// Y is root of tree
		else
		{
			if (curX == curX->parent->left)
				curX->parent->left = curY;
			else
				curX->parent->right = curY;
		}
		curY->right = curX;		// now x is right son of y
		if (curX != nil)
			curX->parent = curY;
	}
	void leftRotate(Node* curX)
	{
		Node* curY = curX->right;		// Y is a right son for X!
		curX->right = curY->left;
		if (curY->left != nil)		// if left son of Y exists
			curY->left->parent = curX;
		if (curY != nil)
			curY->parent = curX->parent;		// parent of x is a parent of y
		if (curX->parent == nil)	// no parent for X
			root = curY;		// Y is root of tree
		else
		{
			if (curX == curX->parent->left)
				curX->parent->left = curY;
			else
				curX->parent->right = curY;
		}
		curY->left = curX;		// now x is left son of y
		if (curX != nil)
			curX->parent = curY;
	}
	void insertFixup(Node* to_insert)	// fix the tree after the "insert" operation
	{
		while ((to_insert->parent->color == RED)&&(to_insert != root))
		{
			if (to_insert->parent == to_insert->parent->parent->left)
			{
				Node* uncle = to_insert->parent->parent->right;
				if (uncle->color == RED)
				{
					// CASE I
					to_insert->parent->color = BLACK;
					uncle->color = BLACK;
					to_insert->parent->parent->color = RED;
					to_insert = to_insert->parent->parent;
				}
				else
				{
					if (to_insert == to_insert->parent->right)
					{
						// CASE II
						to_insert = to_insert->parent;
						leftRotate(to_insert);
					}
					// CASE III
					to_insert->parent->color = BLACK;
					to_insert->parent->parent->color = RED;
					rightRotate(to_insert->parent->parent);
				}
			}
			else
			{
				Node* uncle = to_insert->parent->parent->left;
				if (uncle->color == RED)
				{
					// CASE I
					to_insert->parent->color = BLACK;
					uncle->color = BLACK;
					to_insert->parent->parent->color = RED;
					to_insert = to_insert->parent->parent;
				}
				else
				{
					if (to_insert == to_insert->parent->left)
					{
						// CASE II
						to_insert = to_insert->parent;
						rightRotate(to_insert);
					}
					// CASE III
					to_insert->parent->color = BLACK;
					to_insert->parent->parent->color = RED;
					leftRotate(to_insert->parent->parent);
				}
			}
		}
		root->color = BLACK;
	}
	// helpers for "remove" method
	void transplant(Node* x, Node* y)	// swap x and y
	{
		if (x->parent == nil)
			root = y;
		else
			if (x == x->parent->left)
				x->parent->left = y;
			else x->parent->right = y;
		y->parent = x->parent;
	}
	void removeFixup(Node* x)	// fix the tree after the "remove" operation
	{
		Node* w;
		while ((x != root) && (x->color == BLACK))
		{
			if (x == x->parent->left)
			{
				w = x->parent->right;
				if (w->color == RED)	// brother of x is RED
				{
					// CASE I
					w->color = BLACK;
					x->parent->color = RED;
					leftRotate(x->parent);
					w = x->parent->right;
				}
				if ((w->left->color == BLACK) && (w->right->color == BLACK))	// w is BLACK, his sons are BLACK too
				{
					// CASE II
					w->color = RED;
					x = x->parent;
				}
				else
				{
					// CASE III
					if (w->right->color == BLACK)	// w, brother of x, is BLACK, left son of w is RED, right - BLACK
					{
						w->left->color = BLACK;
						w->color = RED;
						rightRotate(w);
						w = x->parent->right;
					}
					// CASE IV
					w->color = x->parent->color;	// w, brother of x, is BLACK, his right son is RED
					x->parent->color = BLACK;
					w->right->color = BLACK;
					leftRotate(x->parent);
					x = root;
				}
			}
			else
			{
				w = x->parent->left;
				if (w->color == RED)
				{
					// CASE I
					w->color = BLACK;
					x->parent->color = RED;
					rightRotate(x->parent);
					w = x->parent->left;
				}
				if ((w->right->color == BLACK) && (w->left->color == BLACK))
				{
					// CASE II
					w->color = RED;
					x = x->parent;
				}
				else
				{
					// CASE III
					if (w->left->color == BLACK)
					{
						w->right->color = BLACK;
						w->color = RED;
						leftRotate(w);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->left->color = BLACK;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = BLACK;
	}
	void printHelp(Node* current)	// recursive helper method
	{		// can be done with iterators or with recursion
		//dftIterator iter(root, nil);	// iterator starts from root!
		//Node* current;
		string color;
		/*while (iter.has_next())
		{
			current = iter.next();
			if (current->color)
				color = "RED";
			else color = "BLACK";
			cout << "Key: " << current->key << " Data: " << current->value << " Color: " << color << endl;
		}*/
		if (current->color)
			color = "RED";
		else color = "BLACK";
		if (current != nil)
		{
			cout << "Key: " << current->key << " Data: " << current->value << " Color: " << color << endl;
			if (current->right != nil)
				printHelp(current->right);
			if (current->left != nil)
				printHelp(current->left);
		}
		else return;	// there's no node
	}

	void recursiveGet_Keys(Node* current, stack<key_t>* keys_list)	// recursive helper method (get_keys)
	{
		if (current == nil)
			return;		// end of branch
		else
		{
			keys_list->push(current->key);
			if (current->right != nil)
				recursiveGet_Keys(current->right, keys_list);
		}
		if (current->left != nil)
			recursiveGet_Keys(current->left, keys_list);
	}
	void recursiveGet_Values(Node* current, stack<value_t>* values_list)	// recursive helper method (get_values)
	{
		if (current == nil)
			return;		// end of branch
		else
		{
			values_list->push(current->value);
			if (current->right != nil)
				recursiveGet_Values(current->right, values_list);
		}
		if (current->left != nil)
			recursiveGet_Values(current->left, values_list);
	}
	// iterator will help us to print information from tree and make keys and values lists of a tree
	//class dftIterator : public Iterator<Node*>		// what a nice throwback to the Lab3 from previous term!
	//{
	//public:
	//	dftIterator(Node* start, Node* null_nil)
	//	{
	//		cur_map = start;
	//		//current.push(start);
	//		it_nil = null_nil;
	//	}
	//	Node* next()
	//	{
	//		Node* tmp = cur_map;
	//		if (tmp->right != it_nil)
	//			current.push(cur_map->right);
	//		if (tmp->left != it_nil)
	//			cur_map = cur_map->left;
	//		else
	//			if (current.top != nullptr)
	//				cur_map = current.pop();
	//			else cur_map = it_nil;
	//		return tmp;
	//	}
	//	bool has_next()
	//	{
	//		return (cur_map != it_nil);
	//	}
	//	~dftIterator() {}
	//private:
	//	stack<Node*> current;		// stack is built with a pointer on Node from map class as a data
	//	Node* cur_map;
	//	Node* it_nil;
	//};
public:
	map() 
	{
		this->nil = new Node(0, 0, BLACK, nullptr, nullptr, nullptr);
		this->root = nil;
		this->size = 0;
	}
	~map()
	{
		clear();
	}
	void insert(key_t key, value_t value)	// inserts a node to the map
	{
		// new node is ALWAYS RED
		// in some cases it will become BLACK
		Node* y = nil;
		Node* x = root;
		while (x != nil)
		{
			y = x;
			if (key < x->key)
				x = x->left;
			else x = x->right;
		}
		Node* to_insert = new Node(key, value, RED, nil, nil, y);
		if (y == nil)
		{
			root = to_insert;
		}
		else
			if (to_insert->key < y->key)
				y->left = to_insert;
			else
				y->right = to_insert;
		size++;
		insertFixup(to_insert);

		/*Node* x_node = root;
		Node* x_parent = x_node;
		if (x_node == nil)		// RB-tree is empty
		{
			root = new Node(key, value, BLACK, nil, nil, nil);		// creating a root
			return;
		}
		while (x_node != nil)		// moving down to the leafs
		{
			x_parent = x_node;		// it is necessary to save the pointer on parent to end insertion algorythm
			if (key > x_node->key)
			{
				x_node = x_node->right;		// right son is "bigger" than his parent
			}
			else
			{
				x_node = x_node->left;		// left son is "smaller" than his parent
			}
			if (key > x_parent)
			{
				x_parent->right = new Node(key, value, RED, nil, nil, x_parent);	// right son is "bigger" than his parent
				recover(x_parent->right);
			}
			else
			{
				x_parent->left = new Node(key, value, RED, nil, nil, x_parent);	// left son is "smaller" than his parent
				recover(x_parent->left);
			}
		}*/
	}

	void remove(key_t key)	// removes a node from map by key
	{
		if (root == nil)
			throw out_of_range("Nothing to remove: tree is empty.");
		Node* toBeDeleted = root;
		Node* x, * min;
		while (toBeDeleted->key != key)
		{
			if (key > toBeDeleted->key)
				toBeDeleted = toBeDeleted->right;
			else
				toBeDeleted = toBeDeleted->left;
			if (toBeDeleted == nil)
				throw out_of_range("There's no node in RB-Tree with that key.");
		}
		ColorName originalColor = toBeDeleted->color;
		if (toBeDeleted->left == nil)
		{
			x = toBeDeleted->right;
			transplant(toBeDeleted, toBeDeleted->right);
		}
		else
			if (toBeDeleted->right == nil)
			{
				x = toBeDeleted->left;
				transplant(toBeDeleted, toBeDeleted->left);
			}
			else
			{
				min = toBeDeleted->right;
				while (min->left != nil)
					min = min->left;
				originalColor = min->color;
				x = min->right;
				if (min->parent == toBeDeleted)
					x->parent = min;
				else
				{
					transplant(min, min->right);
					min->right = toBeDeleted->right;
					min->right->parent = min;
				}
				transplant(toBeDeleted, min);
				min->left = toBeDeleted->left;
				min->left->parent = min;
				min->color = toBeDeleted->color;
			}
		if (originalColor == BLACK)
			removeFixup(x);
		size--;
	}
	void clear()			// clears map
	{
		while (root != nil)
			remove(root->key);
		cout << "Map is empty." << endl;
	}
	stack<key_t>* get_keys()	// returns array of keys (need to use size and iterator)
	{
		if (root == nil)
			throw out_of_range("Nothing to get: map is empty.");

		//dftIterator iter(root, nil);	// iterator starts from root!
		//Node* current;
		//key_t* out_list = new key_t[size];
		//int i = 0;
		/*while (iter.has_next())
		{
			current = iter.next();
			out_list[i] = current->key;
			i++;
		}*/
		stack<key_t>* out_list = new stack<key_t>();
		recursiveGet_Keys(root, out_list);
		return out_list;
	}
	stack<value_t>* get_values()	// returns array of values (need to use size and iterator)
	{
		// i could do that with iterators but i suck on the topic of iteratos :c
		if (root == nil)
			throw out_of_range("Nothing to get: map is empty.");

		//dftIterator iter(root, nil);	// iterator starts from root!
		//value_t* out_list = new value_t[size];
		//int i = 0;
		/*while (iter.has_next())
		{
			current = iter.next();
			out_list[i] = current->value;
			i++;
		}*/

		stack<value_t>* out_list = new stack<value_t>();
		recursiveGet_Values(root, out_list);
		return out_list;
	}
	void print()
	{
		if (root == nil)
			throw out_of_range("Nothing to print: map is empty.");
		else
		{
			cout << "Root: ";
			printHelp(root);
			cout << endl;
		}
	}
	value_t find(key_t key)	// finds an element by key and returns value from this element
	{
		if (root == this->nil)
			throw out_of_range("Nothing to find: tree is empty.");
		else
		{
			Node* toFind = root;
			while (toFind->key != key)
			{
				if (key > toFind->key)
					toFind = toFind->right;
				else
					toFind = toFind->left;
				if (toFind == this->nil)
					throw out_of_range("There's no node in RB-Tree with that key.");
			}
			return toFind->value;
		}
	}
	size_t give_size()		// incapsulation: method just gives us size (needs for get_keys and get_values made with iterator)
	{
		return size;
	}
};