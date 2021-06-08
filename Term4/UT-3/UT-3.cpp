#include "CppUnitTest.h"
#include <stdexcept>
#include "../Term4_LabWork3/ListL2.h"
#include "../Term4_LabWork3/BellmanFordAlgo.h"
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UT3
{
	TEST_CLASS(UT3)
	{
	public:

		TEST_METHOD(CheckingPointNames)
		{
			int** matrixEdges;
			unsigned edges = 0;
			ListL2<string>* names = new ListL2<string>();
			ifstream file;
			file.open("C:\\Users\\Paul\\source\\repos\\UT-3\\matrix.txt");
			matrixEdges = ReadFromFile(names, file, edges);
			file.close();
			Assert::IsTrue("Gatchina" == names->what_at(0));
			Assert::IsTrue("Vyborg" == names->what_at(1));
			Assert::IsTrue("Tikhvin" == names->what_at(2));
			Assert::IsTrue("Ivangorod" == names->what_at(3));
		}
		TEST_METHOD(BellmanFord_FromAtoA)
		{
			int** matrixEdges;
			unsigned edges = 0;
			ListL2<string>* names = new ListL2<string>();
			ifstream file;
			file.open("C:\\Users\\Paul\\source\\repos\\UT-3\\matrix.txt");
			matrixEdges = ReadFromFile(names, file, edges);
			file.close();

			int* dis = new int[names->give_size()];
			BellmanFord(names, matrixEdges, 0, edges, dis);

			Assert::IsTrue(dis[0] == 0);

			for (unsigned i = 0; i < names->give_size(); i++)
				delete[] matrixEdges[i];
			delete[] matrixEdges;
			delete[] dis;
		}
		//Gatchina;Vyborg;10;20
		//Vyborg;Tikhvin;40;35
		//Gatchina;Tikhvin;14;N/A
		//Ivangorod;Tikhvin;13;N/A
		TEST_METHOD(BellmanFord_FromAtoB_NotExist)
		{
			int** matrixEdges;
			unsigned edges = 0;
			ListL2<string>* names = new ListL2<string>();
			ifstream file;
			file.open("C:\\Users\\Paul\\source\\repos\\UT-3\\matrix.txt");
			matrixEdges = ReadFromFile(names, file, edges);
			file.close();

			int* dis = new int[names->give_size()];
			BellmanFord(names, matrixEdges, 0, edges, dis);

			Assert::IsTrue(dis[3] == INT_MAX/2);

			for (unsigned i = 0; i < names->give_size(); i++)
				delete[] matrixEdges[i];
			delete[] matrixEdges;
			delete[] dis;
		}
	};
}
