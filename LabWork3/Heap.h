#pragma once
#include "Iterator.h"
#include "queue.h"
#include "Stack.h"
class heap
{
public:
		node* root;
		size_t size;
		heap();
		~heap();
		
		size_t give_size();
		bool contains(int key); 
		void insert(int key);
		void remove(int key); 
		void heapify(node* current);
		Iterator* create_dft_iterator();
		Iterator* create_bft_iterator();
		class dftIterator : public Iterator
		{
		public:
			dftIterator(node* start);
			int next() override;
			bool has_next() override;
		private:
			stack* current;
			node* cur_heap;
		};
		class bftIterator : public Iterator
		{
		public:
			bftIterator(node* start);
			int next() override;
			bool has_next() override;
		private:
			queue* current;
		};
};
