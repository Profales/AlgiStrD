#pragma once
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include "ListL2.h"

using namespace std;
int** ReadFromFile(ListL2<string>* names, ifstream &file, unsigned& edges_num)		// e.g. we have lines like "Gatchina;SaintPetersburg;20;10"
{
	// in "names" we will store our names
	string temp, usersText;
	int count, i = 0, j = 0, edges_tmp = 0;
	while (!file.eof())
		{
			getline(file, usersText);
			count = 0;				// in every line we have only 4 positions - town1, town2, way1, way2
			for (size_t k = 0; k < usersText.size(); k++)
			{
				temp = "";
				while ((usersText[k] != ';') && (usersText[k] != ',') && (k != usersText.size()))		// user can divide it by , or ;
					temp += usersText[k++];		// building a string by 1 symbol at iteration
				switch (count)
				{
					case 0:
					{
						if (names->FindAnElement(temp) == -1)
							names->push_back(temp);
						break;
					}
					case 1:
					{
						if (names->FindAnElement(temp) == -1)
						{
							names->push_back(temp);
							//names->print();
						}
						break;
					}
					case 2:
					{
						if (temp != "N/A")
							edges_tmp++;
						break;
					}
					case 3:
					{
						if (temp != "N/A")
							edges_tmp++;
						break;
					}
				}
				count++;
			}
		}

		file.close();
		file.open("matrix.txt");
		// every {u, v, w} in greatMatrix is just an edge of graph
		// it can be read like "from u to v way costs w"
		int** greatMatrix = new int* [edges_tmp];
		for (int i = 0; i < edges_tmp; i++)
			greatMatrix[i] = new int[3];
		//for (int i = 0; i < edges_tmp; i++)
		//	for (int j = 0; j < 3; j++)
		//		greatMatrix[i][j] = 0;		// 0 in matrix means N/A
		
		while (!file.eof())
		{
			getline(file, usersText);
			count = 0;				// in every line we have only 4 positions - town1, town2, way1, way2
			for (size_t k = 0; k < usersText.size(); k++)
			{
				temp = "";
				while ((usersText[k] != ';') && (usersText[k] != ',') && (k != usersText.size()))		// user can divide it by , or ;
					temp += usersText[k++];		// building a string by 1 symbol at iteration
				switch (count)
				{
					case 0:
					{
						if (names->FindAnElement(temp) != -1)
							i = names->FindAnElement(temp);
						break;
					}
					case 1:
					{
						if (names->FindAnElement(temp) != -1)
							j = names->FindAnElement(temp);
						break;
					}
					case 2:				// greatMatrix is an adjacency matrix; greatMatrix[i][j] == greatMatrix[j][i]
					{
						if (temp != "N/A")			// 0 in matrix means N/A
						{
							greatMatrix[edges_num][0] = i;
							greatMatrix[edges_num][1] = j;
							greatMatrix[edges_num][2] = atoi(temp.c_str());			// str.c_str() to make string a const char* value
							edges_num++;
						}
						break;
					}
					case 3:				// greatMatrix is an adjacency matrix; greatMatrix[i][j] == greatMatrix[j][i]
					{
						if (temp != "N/A")			// 0 in matrix means N/A
						{
							greatMatrix[edges_num][0] = j;
							greatMatrix[edges_num][1] = i;
							greatMatrix[edges_num][2] = atoi(temp.c_str());			// str.c_str() to make string a const char* value
							edges_num++;
						}
						break;
					}				// a little of explaining: we have line "Moscow;Khabarovsk;10;20"
									// case 2 and case 3 say that we are building an array of edges
									// first edge is {0, 1, 10} and it means that from Moscow to Khabarovsk the way costs 10
									// second edge is {1, 0, 20} and it means that from Moscow to Khabarovsk the way costs 20
				}
				count++;
			}
		}
	file.close();
	return greatMatrix;
}

void BellmanFord(ListL2<string>* names, int** greatMatrix, int source, int Edges, int*& distances)
{
	for (int i = 0; i < names->give_size(); i++)
		distances[i] = INT_MAX / 2;			// INT_MAX/2 == infinity
	distances[source] = 0;		// our start
	for (int i = 0; i < names->give_size() - 1; i++)
	{
		for (int j = 0; j < Edges; j++) 
		{
			if ((distances[greatMatrix[j][0]] != INT_MAX) && (distances[greatMatrix[j][0]] + greatMatrix[j][2] < distances[greatMatrix[j][1]]))
				distances[greatMatrix[j][1]] = distances[greatMatrix[j][0]] + greatMatrix[j][2];
		}
	}

	// now we are checking if there's some negative weight cycle
	for (int i = 0; i < Edges; i++)
	{
		int x = greatMatrix[i][0];
		int y = greatMatrix[i][1];
		int weight = greatMatrix[i][2];
		if ((distances[x] != INT_MAX/2) && (distances[x] + weight < distances[y]))
			cout << "Граф содержит отрицательный цикл." << endl;
	}
	cout << "Все пути из " << names->what_at(source) << " перечислены ниже." << endl; 
	cout << "Первый столбец - это пункты назначения, соответствующие им числа во втором столбце - длины дорог." << endl;
	cout << "N/A означает, что такого пути нет." << endl;
	for (int i = 0; i < names->give_size(); i++)
		if (distances[i] != INT_MAX / 2)
			cout << names->what_at(i) << "\t\t" << distances[i] << endl;
		else cout << names->what_at(i) << "\t\t" << "N/A" << endl;
	cout << endl;
}

void Summing()
{
	// source is the index of city from which
	int** matrixEdges;
	unsigned edges = 0;
	ListL2<string>* names = new ListL2<string>();
	ifstream file;
	file.open("matrix.txt");
	if (!file)
	{
		throw "No such file in directory.";
	}
	else matrixEdges = ReadFromFile(names, file, edges);
	file.close();
	int* dis = new int[names->give_size()];
	for (int i = 0; i < names->give_size(); i++)
		BellmanFord(names, matrixEdges, i, edges, dis);

	for (unsigned i = 0; i < edges; i++)
		delete[] matrixEdges[i];
	delete[] matrixEdges;

}