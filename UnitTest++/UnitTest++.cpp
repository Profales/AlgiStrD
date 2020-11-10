#include "CppUnitTest.h"
#include <stdexcept>
#include "..\LabWork1\LinkedList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		LinkedList* list, *list2;
		TEST_METHOD_INITIALIZE(setUp)
		{
			list = new LinkedList();
			list2 = new LinkedList();
		}
		TEST_METHOD_CLEANUP(cleanUp)
		{
			delete list;
			delete list2;
		}
		TEST_METHOD(pop_back_equal)
		{
			list->push_back(1);
			list->push_back(2);
			list->push_back(3);
			list->pop_back();
			Assert::AreEqual(list->at(1), 2); // 2nd element == 2?
		}
		TEST_METHOD(pop_back_size)
		{
			list->push_back(1);
			list->push_back(2);
			list->pop_back();
			Assert::AreEqual(int(list->get_size()), 1); // size == 1?
		}
		TEST_METHOD(pop_back_zero)
		{
			list->pop_back();
			Assert::AreEqual(int(list->get_size()), 0); // empty list?
		}
		TEST_METHOD(is_really_empty)
		{
			list->push_back(1);
			list->pop_back();
			Assert::AreEqual(int(list->isEmpty()), 1); // is it seen as empty?
		}
		TEST_METHOD(at_incorrect_index)
		{
			try {
				list->at(-1);
			}
			catch (std::out_of_range e) {
				Assert::AreEqual("This index is greater than size of that list.", e.what());
			}
		}
		TEST_METHOD(push_front_equal)
		{
			list->push_front(1);
			list->push_front(2);
			list->push_front(3);
			Assert::AreEqual(list->at(1), 2); // 2nd element == 2?
		}
		TEST_METHOD(push_back_equal)
		{
			list->push_back(1);
			list->push_back(2);
			list->push_back(3);
			Assert::AreEqual(list->at(2), 3); // 3rd element == 3?
		}
		TEST_METHOD(pop_front_equal)
		{
			list->push_back(1);
			list->push_back(2);
			list->push_back(3);
			list->pop_front();
			Assert::AreEqual(list->at(0), 2); // 1st element == 3?
		}
		TEST_METHOD(insert_check)
		{
			list->push_back(1);
			list->push_back(2);
			list->push_back(3);
			list->insert(4, 1);
			Assert::AreEqual(list->at(1), 4); // 2nd element == 4?
		}
		TEST_METHOD(remove_check)
		{
			list->push_back(1);
			list->push_back(2);
			list->push_back(3);
			list->remove(1);
			Assert::AreEqual(list->at(1), 3); // 2nd element == 3?
		}
		TEST_METHOD(push_back_size)
		{
			list->push_back(1);
			Assert::AreEqual(int(list->get_size()), 1); // 1 element in the list?
		}
		TEST_METHOD(push_front_size)
		{
			list->push_front(1);
			Assert::AreEqual(int(list->get_size()), 1); // 1 element in the list?
		}
		TEST_METHOD(pop_front_size)
		{
			list->push_back(1);
			list->push_back(2);
			list->push_back(3);
			list->pop_front();
			Assert::AreEqual(int(list->get_size()), 2); // 2 elements in the list?
		}
		TEST_METHOD(pop_front_zero)
		{
			list->pop_front();
			Assert::AreEqual(int(list->get_size()), 0); // empty list?
		}
		TEST_METHOD(clear_check)
		{
			list->push_back(1);
			list->push_back(2);
			list->push_back(3);
			list->clear();
			Assert::AreEqual(int(list->get_size()), 0); // empty list?
		}
		TEST_METHOD(set_check)
		{
			list->push_back(1);
			list->push_back(2);
			list->push_back(3);
			list->set(2, 4);
			Assert::AreEqual(list->at(2), 4); // 3rd element == 4?
		}
		TEST_METHOD(push_back_list_size)
		{
			list->push_back(1);
			list->push_back(2);
			list->push_back(3);
			list2->push_back(4);
			list2->push_back(5);
			list2->push_back(6);
			list->push_back_list(list2);
			Assert::AreEqual(int(list->get_size()), 6); // 6 elements in the list?
		}
		TEST_METHOD(push_back_list_elements)
		{
			list->push_back(1);
			list->push_back(2);
			list->push_back(3);
			list2->push_back(4);
			list2->push_back(5);
			list2->push_back(6);
			list->push_back_list(list2);
			Assert::AreEqual(list->at(5), 6); // 6th element == 6?
		}
		TEST_METHOD(get_size_check)
		{
			list->push_back(1);
			list->push_back(2);
			list->push_back(3);
			Assert::AreEqual(int(list->get_size()), 3); // 3 elements in the list?
		}
		TEST_METHOD(get_size_empty)
		{
			Assert::AreEqual(int(list->get_size()), 0); // empty list?
		}
		TEST_METHOD(insert_incorrect_index)
		{
			try {
				list->insert(1, -1);
			}
			catch (std::out_of_range e) {
				Assert::AreEqual("This index is greater than size of that list.", e.what());
			}
		}
		TEST_METHOD(set_incorrect_index)
		{
			try {
				list->set(-1, 1);
			}
			catch (std::out_of_range e) {
				Assert::AreEqual("This index is greater than size of that list.", e.what());
			}
		}
		TEST_METHOD(remove_incorrect_index)
		{
			try {
				list->remove(-1);
			}
			catch (std::out_of_range e) {
				Assert::AreEqual("This index is greater than size of that list.", e.what());
			}
		}
	};
}
