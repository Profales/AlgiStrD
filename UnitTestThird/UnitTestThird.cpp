#include "CppUnitTest.h"
#include "../Lab3/Heap.h"
#include "../Lab3/Iterator.h"
#include "../Lab3/queue.h"
#include "../Lab3/Stack.h"
#include "../Lab3/Node.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestThird
{
	TEST_CLASS(UnitTestThird)
	{
	public:
		heap* for_test;
		TEST_METHOD_INITIALIZE(setUp)
		{
			for_test = new heap();
		}
		TEST_METHOD_CLEANUP(cleanUp)
		{
			delete for_test;
		}

		TEST_METHOD(insert_size)
		{
			for_test->insert(5);
			for_test->insert(3);
			for_test->insert(2);
			Assert::AreEqual(for_test->give_size(), size_t(3));
		}
		TEST_METHOD(insert_node_root)
		{
			for_test->insert(5);
			for_test->insert(3);
			for_test->insert(2);
			Assert::AreEqual(for_test->root->key, 5);
		}
		TEST_METHOD(insert_node_left)
		{
			for_test->insert(5);
			for_test->insert(3);
			for_test->insert(2);
			Assert::AreEqual(for_test->root->left_son->key, 3);
		}
		TEST_METHOD(insert_node_right)
		{
			for_test->insert(5);
			for_test->insert(3);
			for_test->insert(2);
			Assert::AreEqual(for_test->root->right_son->key, 2);
		}
		TEST_METHOD(remove_size_true)
		{
			for_test->insert(5);
			for_test->insert(3);
			for_test->insert(2);
			for_test->remove(3);
			Assert::AreEqual(for_test->give_size(), size_t(2));
		}
		TEST_METHOD(remove_size_false)
		{
			for_test->insert(5);
			for_test->insert(3);
			for_test->insert(2);
			for_test->remove(6);
			Assert::AreEqual(for_test->give_size(), size_t(3));
		}
		TEST_METHOD(remove_node)
		{
			for_test->insert(5);
			for_test->insert(3);
			for_test->insert(2);
			for_test->remove(5);
			Assert::AreEqual(for_test->root->key, 3);
		}
		TEST_METHOD(contains_true)
		{
			for_test->insert(5);
			for_test->insert(3);
			for_test->insert(2);
			Assert::AreEqual(for_test->contains(5), true);
		}
		TEST_METHOD(contains_false)
		{
			for_test->insert(5);
			for_test->insert(3);
			for_test->insert(2);
			Assert::AreEqual(for_test->contains(6), false);
		}
		TEST_METHOD(dftIterator_)
		{
			for_test->insert(5);
			for_test->insert(3);
			for_test->insert(2);
			for_test->insert(4);
			for_test->insert(1);
			Iterator* dftIterator = for_test->create_dft_iterator();
			int array[5] = { 5, 4, 3, 1, 2 };
			bool flag = true;
			int i = 0;
			while (dftIterator->has_next())
			{
				if (dftIterator->next() != array[i])
					flag = false;
				i++;
			}
			Assert::AreEqual(true, flag);
		}
		TEST_METHOD(bftIterator_)
		{
			for_test->insert(5);
			for_test->insert(3);
			for_test->insert(2);
			for_test->insert(4);
			for_test->insert(1);
			Iterator* bftIterator = for_test->create_bft_iterator();
			int array[5] = {5, 4, 2, 3, 1};
			bool flag = true;
			int i = 0;
			while (bftIterator->has_next())
			{
				if (bftIterator->next() != array[i])
					flag = false;
				i++;
			}
			Assert::AreEqual(true, flag);
		}
	};
}
