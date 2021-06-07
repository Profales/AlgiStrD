#include "CppUnitTest.h"
#include <stdexcept>
#include "../Term4_LabWork2/DeCodesAndEnCodes.h"
#include "../Term4_LabWork2/Stack.h"
#include "../Term4_LabWork2/Map.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UT2
{
		TEST_CLASS(FunctionTest)
		{
		public:
			TEST_METHOD(SearchMiddleTest)
			{
				int freqs[6]{ 6, 5, 4, 3, 2, 2 };
				int median = SliceItUp(freqs, 0, 6);
				Assert::IsTrue(median == 1);
			}
			TEST_METHOD(DoubleSort)
			{
				int* freqs = new int[6] { 2, 6, 3, 5, 2, 4 };
				char* symbs = new char[6]{ 'f', 'a', 'd', 'b', 'e', 'c'};
				char* toControl = new char[6]{ 'a', 'b' , 'c', 'd','e','f'};

				SortTwoArrays(freqs, symbs, 6);

				for (int i = 0; i < 6; i++)
				{
					Assert::IsTrue(symbs[i] == toControl[i]);
				}
			}
			TEST_METHOD(EncodeDecode)
			{
				string str = "to be or not to be";
				string test = "011 10 11 001 010 11 10 0000 11 0001 10 011 11 011 10 11 001 010";
				string encoding_result, decoding_result;
				Summing(str, encoding_result, decoding_result);
				for (int i = 0; i < encoding_result.length() - 1; i++)
				{
					Assert::IsTrue(encoding_result[i] == test[i]);
				}
				Assert::IsTrue(decoding_result == str);
			}
		};
}
