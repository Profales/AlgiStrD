#include "CppUnitTest.h"
#include <stdexcept>
#include "..\LabWork2\LabWork2.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:
		int* array;
		TEST_METHOD_INITIALIZE(setUp)
		{
			array = new int[10];
			for (int i = 0; i < 10; i++)
			{
				array[i] = rand();
			}
		}
		TEST_METHOD_CLEANUP(cleanUp)
		{
			delete[] array;
		}
		TEST_METHOD(is_not_Sorted)
		{
			Assert::IsFalse(isSorted(array, 10));
		}
		TEST_METHOD(is_Sorted_for_real)
		{
			for (int i = 0; i < 10; i++)
			{
				array[i] = i;
			}
			Assert::IsTrue(isSorted(array, 10));
		}
		TEST_METHOD(BogoSort_is_Sorted)
		{
			BogoSort(array, 10);
			Assert::IsTrue(isSorted(array, 10));
		}
		TEST_METHOD(QuickSort_is_Sorted)
		{
			QuickSort(array, 0, 9);
			Assert::IsTrue(isSorted(array, 10));
		}
		TEST_METHOD(BubbleSort_is_Sorted)
		{
			BubbleSort(array, 10);
			Assert::IsTrue(isSorted(array, 10));
		}
		TEST_METHOD(BinarySearch_not_found)
		{
			for (int i = 0; i < 10; i++) 
			{
				array[i] = i;
			}
			try 
			{
				BinarySearch(array, 30, 10);
			}
			catch (std::out_of_range e) 
			{
				Assert::AreEqual("Not found", e.what());
			}
		}
		TEST_METHOD(BinarySearch_found)
		{
			for (int i = 0; i < 10; i++)
			{
				array[i] = i;
			}
			try
			{
				BinarySearch(array, 9, 10);
			}
			catch (std::out_of_range e)
			{
				Assert::AreEqual("Found: A[9] = 9", e.what());
			}
		}
		TEST_METHOD(CountingSort_is_Sorted)
		{
			char array_char[] = {'a', '0', '1', '0', '5', '4', '2', 'b'};
			CountingSort(array_char, 8);
			Assert::IsTrue(isSorted(array_char, 7));
		}
		TEST_METHOD(BubbleSort_is_equal)
		{
			for (int i = 0; i < 10; i++)
			{
				array[9 - i] = i;
			}
			BubbleSort(array, 10);
			Assert::AreEqual(array[0], 0);
		}
		TEST_METHOD(QuickSort_is_equal)
		{
			for (int i = 0; i < 10; i++)
			{
				array[9-i] = i;
			}
			QuickSort(array, 0, 9);
			Assert::AreEqual(array[0], 0);
		}
		TEST_METHOD(BogoSort_is_equal)
		{
			for (int i = 0; i < 10; i++)
			{
				array[9 - i] = i;
			}
			BogoSort(array, 10);
			Assert::AreEqual(array[0], 0);
		}
		TEST_METHOD(CountingSort_is_equal)
		{
			char array_char[] = { 'a', '0', '1', '0', '5', '4', '2', 'b' };
			CountingSort(array_char, 8);
			Assert::AreEqual(array_char[0], '0');
		}
	};
}
