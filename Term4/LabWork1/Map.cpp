/*#include "Map.h"
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename key_t, typename value_t>
map<key_t, value_t>::map()
{
	this->nil = new Node(0, 0, BLACK, nullptr, nullptr, nullptr);
	this->root = nil;
	this->size = 0;
}

template <typename key_t, typename value_t>
map<key_t, value_t>::~map()
{
	clear();
}

template <typename key_t, typename value_t>
void map<key_t, value_t>::insert(key_t key, value_t value)		// insert to map by key and value
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

}

template <typename key_t, typename value_t>
void map<key_t, value_t>::insertFixup(Node* to_insert)
{
	while (to_insert->parent->color == RED)
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
					leftRotate(to_insert);
				}
				// CASE III
				to_insert->parent->color = BLACK;
				to_insert->parent->parent->color = RED;
				rightRotate(to_insert->parent->parent);
			}
		}
	}
	this->root->color = BLACK;
}

template <typename key_t, typename value_t>
void map<key_t, value_t>::transplant(Node* x, Node* y)
{
	if (x->parent == nil)
		root = y;
	else
		if (x == x->parent->left)
			x->parent->left = y;
		else x->parent->right = y;
	y->parent = x->parent;
}

template <typename key_t, typename value_t>
void map<key_t, value_t>::remove(key_t key)		// remove from map by key
{
	if (root == nil)
		throw out_of_range("Nothing to remove: tree is empty.");
	Node* toBeDeleted = root;
	while (toBeDeleted->key != key)
	{
		if (key > toBeDeleted->key)
			toBeDeleted = toBeDeleted->right;
		else
			toBeDeleted = toBeDeleted->left;
		if (toBeDeleted == nil)
			throw out_of_range("There's no node in RB-Tree with that key.");
	}
	int originalColor = toBeDeleted->color;
	Node* x, min;
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

template <typename key_t, typename value_t>
void map<key_t, value_t>::removeFixup(Node* x)		// this will be called then RB-tree is broken after removing a node
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

template <typename key_t, typename value_t>
void map<key_t, value_t>::leftRotate(Node* curX)		// Y must be a right son for X
{
	if (curX->right == nil)		// the main condition is broken
		return;
	// else
	Node* curY = curX->right;		// Y is a right son for X!

	if (curY->left != nil)		// if left son of Y exists
		curY->left->parent = curX;
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
	curX->parent = curY;
}

template <typename key_t, typename value_t>
void map<key_t, value_t>::rightRotate(Node* curX)
{
	if (curX->left == nil)		// the main condition is broken
		return;
	// else
	Node* curY = curX->left;		// Y is a left son for X!

	if (curY->right != nil)		// if right son of Y exists
		curY->rightt->parent = curX;
	curY->parent = curX->parent;		// parent of x is a parent of y
	if (curX->parent == nil)	// no parent for X
		root = curY;		// Y is root of tree
	else
	{
		if (curX == curX->parent->right)
			curX->parent->right = curY;
		else
			curX->parent->left = curY;
	}
	curY->right = curX;		// now x is right son of y
	curX->parent = curY;
}

template <typename key_t, typename value_t>
value_t map<key_t, value_t>::find(key_t key)
{
	if (root == nil)
		throw out_of_range("Nothing to remove: tree is empty.");
	Node* toFind = root;
	while (toFind->key != key)
	{
		if (key > toFind->key)
			toFind = toFind->right;
		else
			toFind = toFind->left;
		if (toFind == nil)
			throw out_of_range("There's no node in RB-Tree with that key.");
	}
	return toFind->value;
}

template <typename key_t, typename value_t>
void map<key_t, value_t>::clear()	// clear map
{
	while (root != nil)
		remove(root->key);
	cout << "Map is empty." << endl;
}

template <typename key_t, typename value_t>
key_t* map<key_t, value_t>::get_keys()		// returns array of keys (need to use size and iterator)
{
	if (root == nil)
		throw out_of_range("Nothing to get: map is empty.");
	dftIterator iter = create_dft_iterator();	// iterator starts from root!
	Node* current;
	key_t* out_list = new key_t[size];
	int i = 0;
	while (iter.has_next())
	{
		current = iter.next();
		out_list[i] = current->key;
		i++;
	}
	return out_list;
}

template <typename key_t, typename value_t>
value_t* map<key_t, value_t>::get_values()	// returns array of values (need to use size and iterator)
{
	if (root == nil)
		throw out_of_range("Nothing to get: map is empty.");
	dftIterator iter = create_dft_iterator();	// iterator starts from root!
	Node* current;
	value_t* out_list = new value_t[size];
	int i = 0;
	while (iter.has_next())
	{
		current = iter.next();
		out_list[i] = current->value;
		i++;
	}
	return out_list;
}

template <typename key_t, typename value_t>
void map<key_t, value_t>::print()		// print to console (need to use iterator)
{
	if (root == nil)
		throw out_of_range("Nothing to print: map is empty.");
	dftIterator iter = create_dft_iterator();	// iterator starts from root!
	Node* current;
	while (iter.has_next())
	{
		current = iter.next();
		cout << "Key: " << current->key << " Data: " << current->value << " Color: " << current->color << endl;
	}
}

template <typename key_t, typename value_t>
size_t map<key_t, value_t>::give_size()		// gives us size (to make "get_keys" and "get_values" correctly)
{
	return size;
}
*/