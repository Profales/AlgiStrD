/*#include "Stack.h"

using namespace std;
template <class T>
stack<T>::stack()
{
	top = nullptr;
}
template <class T>
void stack<T>::push(T to_push)
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
template <class T>
T stack<T>::pop()
{
	if (top == nullptr)
		return nullptr;
	T tmp = top->info;
	top = top->prev;
	top->next = nullptr;
	return tmp;
}
template <class T>
stack<T>::~stack() 
{
	T tmp;
	while (top)
	{
		tmp = pop();
	}
}*/