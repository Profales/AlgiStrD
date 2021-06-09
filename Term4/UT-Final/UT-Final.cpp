#include "CppUnitTest.h"
#include "../Term4_TermWork/ListL2.h"
#include "../Term4_TermWork/GraphsAndStuff.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UTFinal
{
	TEST_CLASS(UTFinal)
	{
	public:
		TEST_METHOD(_get_Test)
		{
			int dim = 3;
			Graph Test(dim);
			Assert::IsTrue(Test.Get(0, 1) == 0);
		}
		TEST_METHOD(_set_Test)
		{
			int dim = 3;
			Graph Test(dim);
			Test.Set(2, 2, 3);
			Assert::IsTrue(Test.Get(2, 2) == 3);
		}
		TEST_METHOD(bfs_Test)
		{
			int dim = 3;
			Graph* Test = new Graph(dim);
			Graph* Flow = new Graph(3);
			Test->Set(0, 1, 1);
			Test->Set(0, 2, 1);
			Test->Set(1, 2, 1);
			Assert::IsTrue(Test->BFS(*Flow)->what_at(0) == 0);
			Assert::IsTrue(Test->BFS(*Flow)->what_at(1) == 2);
		}
		TEST_METHOD(ReadFileAndTakeNamesTest)
		{
			ifstream read("C:\\Users\\Paul\\source\\repos\\Term4_TermWork\\task.txt");
			int VertexesNumber = 0;
			string UniqueVertexes = "";
			ReadFileAndTakeNames(UniqueVertexes, VertexesNumber, read);
			VertexesNumber = VertexesNumber - 1;
			char* names = new char[VertexesNumber];
			for (int k = 0; k < VertexesNumber; ++k)
				names[k] = UniqueVertexes[k];
			read.close();
			Assert::IsTrue(names[0] == 'S');
			Assert::IsTrue(names[1] == 'O');
			Assert::IsTrue(names[2] == 'P');
			Assert::IsTrue(names[3] == 'Q');
			Assert::IsTrue(names[4] == 'R');
			Assert::IsTrue(names[5] == 'T');
			Assert::IsTrue(VertexesNumber == 6);
			delete[] names;
		}
	};
}
