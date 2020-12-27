#include "CppUnitTest.h"
#include "..\CourseWork3\Prefix.h"
#include "..\CourseWork3\PrefixList.h"
#include "..\CourseWork3\Stack.h"
#include "..\CourseWork3\Node.h"
#include <stdexcept>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestFinal
{
	TEST_CLASS(UnitTestFinal)
	{
	public:
		
		PrefixList* for_test;

		TEST_METHOD_INITIALIZE(setUp)
		{
			for_test = new PrefixList();
		}

		TEST_METHOD_CLEANUP(cleanUp)
		{
			delete for_test;
		}

		TEST_METHOD(add_operator_calc)
		{
			string to_input = {"3+4"};
			for_test->input_and_perform(to_input);
			Assert::AreEqual(for_test->calculate(), 7.0);
		}
		TEST_METHOD(sub_operator_calc)
		{
			string to_input = { "1.5-0.01" };
			for_test->input_and_perform(to_input);
			Assert::AreEqual(for_test->calculate(), 1.49);
		}
		TEST_METHOD(mult_operator_calc)
		{
			string to_input = { "1*2.2" };
			for_test->input_and_perform(to_input);
			Assert::AreEqual(for_test->calculate(), 2.2);
		}
		TEST_METHOD(div_operator_calc)
		{
			string to_input = { "3+1/2" };
			for_test->input_and_perform(to_input);
			Assert::AreEqual(for_test->calculate(), 3.5);
		}
		TEST_METHOD(pow_operator_calc)
		{
			string to_input = { "2^11" };
			for_test->input_and_perform(to_input);
			Assert::AreEqual(for_test->calculate(), 2048.0);
		}
		TEST_METHOD(brackets_1)
		{
			string to_input = { "(10+2)/2" };
			for_test->input_and_perform(to_input);
			Assert::AreEqual(for_test->calculate(), 6.0);
		}
		TEST_METHOD(brackets_2)
		{
			string to_input = { "8/(2+2)^2" };
			for_test->input_and_perform(to_input);
			Assert::AreEqual(for_test->calculate(), 0.5);
		}
		TEST_METHOD(cos_function_1)
		{
			string to_input = { "cos(0)" };
			for_test->input_and_perform(to_input);
			Assert::AreEqual(for_test->calculate(), 1.0);
		}
		TEST_METHOD(cos_function_2)
		{
			string to_input = { "2+cos(pi)" };
			for_test->input_and_perform(to_input);
			Assert::AreEqual(for_test->calculate(), 1.0);
		}
		TEST_METHOD(sin_function)
		{
			string to_input = { "1 + sin(pi/2)" };
			for_test->input_and_perform(to_input);
			Assert::AreEqual(for_test->calculate(), 2.000);
		}
		TEST_METHOD(tg_function)
		{
			string to_input = { "tg(0)" };
			for_test->input_and_perform(to_input);
			Assert::AreEqual(for_test->calculate(), 0.0);
		}
		TEST_METHOD(log_function)
		{
			string to_input = { "log(10)" };
			for_test->input_and_perform(to_input);
			Assert::AreEqual(for_test->calculate(), 1.0);
		}
		TEST_METHOD(log_function_with_expression)
		{
			string to_input = { "log(15-5)" };
			for_test->input_and_perform(to_input);
			Assert::AreEqual(for_test->calculate(), 1.0);
		}
		TEST_METHOD(ln_function)
		{
			string to_input = { "ln(e)" };
			for_test->input_and_perform(to_input);
			Assert::AreEqual(for_test->calculate(), 1.0);
		}
		TEST_METHOD(sqrt_function)
		{
			string to_input = { "sqrt(100)" };
			for_test->input_and_perform(to_input);
			Assert::AreEqual(for_test->calculate(), 10.0);
		}
		TEST_METHOD(error_1)
		{
			try 
			{
				string to_input = { "" };
				for_test->input_and_perform(to_input);
			}
			catch (const char* error) 
			{
				Assert::AreEqual("Invalid input. Wrong symbols.", error);
			}
		}
		TEST_METHOD(error_2)
		{
			try 
			{
				string to_input = { "1+2)" };
				for_test->input_and_perform(to_input);
			}
			catch (const char* error)
			{
				Assert::AreEqual("Invalid input. Some brackets aren't closed.", error);
			}
		}
		TEST_METHOD(error_3)
		{
			try {
				string to_input = { "1+()" };
				for_test->input_and_perform(to_input);
			}
			catch (const char* error) 
			{
				Assert::AreEqual("Invalid input. Expression like () was not expected.", error);
			}
		}
		TEST_METHOD(error_4)
		{
			try
			{
				string to_input = { "1+(2" };
				for_test->input_and_perform(to_input);
			}
			catch (const char* error)
			{
				Assert::AreEqual("Invalid input. Expression with unclosed brackets was not expected.", error);
			}
		}
		TEST_METHOD(error_5)
		{
			try {
				string to_input = { "1+1+" };
				for_test->input_and_perform(to_input);
			}
			catch (const char* error) 
			{
				Assert::AreEqual("Invalid input. Too much operators.", error);
			}
		}
	};
}
