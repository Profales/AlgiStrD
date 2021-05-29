#include "CppUnitTest.h"
#include <stdexcept>
#include "../Term4_LabWork1/Stack.h"
#include "../Term4_LabWork1/Map.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Term4UT1
{
	TEST_CLASS(Term4UT1)
	{
	public:
		map<int, char>* RBtree;
		TEST_METHOD_INITIALIZE(SetUp)
		{
			RBtree = new map<int, char>();
		}
		TEST_METHOD_CLEANUP(cleanUp)
		{
			delete RBtree;
		}
		TEST_METHOD(insert_check_find_1)
		{
			RBtree->insert(1, 'a');
			RBtree->insert(2, 'b');
			RBtree->insert(3, 'c');
			Assert::AreEqual(RBtree->find(3), 'c');
		}
		TEST_METHOD(insert_check_find_2)
		{
			try
			{
				RBtree->insert(1, 'a');
				RBtree->insert(2, 'b');
				RBtree->insert(3, 'c');
				char symbol = RBtree->find(4);
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "There's no node in RB-Tree with that key.");
			}
		}
		TEST_METHOD(insert_to_tree_size)
		{
			RBtree->insert(1, 'a');
			Assert::AreEqual((size_t)1, RBtree->give_size());
		}
		TEST_METHOD(find_empty)
		{
			try
			{
				RBtree->insert(5, 'c');
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "Nothing to find: tree is empty.");
			}
		}
		TEST_METHOD(print_empty)
		{
			try
			{
				RBtree->print();
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "Nothing to print: map is empty.");
			}
		}
		TEST_METHOD(remove_empty)
		{
			try
			{
				RBtree->remove(1);
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "Nothing to remove: tree is empty.");
			}
		}
		TEST_METHOD(remove_no_such_elem)
		{
			try
			{
				RBtree->insert(2, 'c');
				RBtree->remove(1);
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "There's no node in RB-Tree with that key.");
			}
		}
		TEST_METHOD(true_remove_find)
		{
			try
			{
				RBtree->insert(2, 'c');
				RBtree->insert(1, 'b');
				RBtree->remove(1);
				char c = RBtree->find(2);
				Assert::AreEqual(c, 'c');
				RBtree->remove(2);
				c = RBtree->find(1);
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "Nothing to find: tree is empty.");
			}
		}
		TEST_METHOD(get_keys_what_at)
		{
			stack<int>* keys_list;
			RBtree->insert(1, 'a');
			RBtree->insert(2, 'b');
			RBtree->insert(3, 'c');
			keys_list = RBtree->get_keys();
			Assert::IsTrue((keys_list->what_at(0) == 1) && (keys_list->what_at(1) == 3) && (keys_list->what_at(2) == 2));
		}
		TEST_METHOD(get_values_what_at)
		{
			stack<char>* values_list;
			RBtree->insert(1, 'a');
			RBtree->insert(2, 'b');
			RBtree->insert(3, 'c');
			values_list = RBtree->get_values();
			Assert::IsTrue((values_list->what_at(0) == 'a') && (values_list->what_at(1) == 'c') && (values_list->what_at(2) == 'b'));
		}
		TEST_METHOD(clear_test)
		{
			RBtree->insert(1, 'a');
			RBtree->insert(2, 'b');
			RBtree->insert(3, 'c');
			RBtree->clear();
			Assert::AreEqual((size_t)0, RBtree->give_size());
		}
		TEST_METHOD(size_empty)
		{
			Assert::AreEqual((size_t)0, RBtree->give_size());
		}
	};
}
