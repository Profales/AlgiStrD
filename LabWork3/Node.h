#pragma once
class node
{
public:
	node();
	~node() {};
	int key;
	node* left_son;
	node* right_son;
	node* parent;
};