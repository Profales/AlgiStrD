#pragma once
#include "ListL2.h"
#include <iostream>
#include <fstream>

using namespace std;

class Graph
{
public:
    int dimG;
    int** matrixG;
	Graph(int dimG);
	~Graph();
	void Set(int i, int j, int info);
	int Get(int i, int j);
	ListL2<int>* BFS(Graph& Flow);
};

Graph::Graph(int dimG)
{
    this->dimG = dimG;
    matrixG = new int*[dimG];
    for (int i = 0; i < dimG; i++)
        matrixG[i] = new int[dimG];
    for (int i = 0; i < dimG; i++)
        for (int j = 0; j < dimG; j++)
            matrixG[i][j] = 0;
}
Graph::~Graph()
{
    for (int i = 0; i < this->dimG; ++i)
        delete[] matrixG[i];
    delete[] matrixG;
}
// in C# it can be made as {get; set;}
void Graph::Set(int i, int j, int info)
{
    matrixG[i][j] = info;
}
int Graph::Get(int i, int j)
{
    return matrixG[i][j];
}

ListL2<int>* Graph::BFS(Graph& Flow)
{
    ListL2<int> queue;
    ListL2<int>* path = new ListL2<int>;
    int* level = new int[dimG];
    bool* visited = new bool[dimG];
    for (int i = 0; i < dimG; i++)
        visited[i] = false;
    level[0] = 0;
    queue.push_back(0);
    visited[0] = true;
    while (!(queue.isEmpty()))
    {
        int u = queue.what_at(0);
        queue.pop_front();
        for (int i = 0; i < dimG; i++)
        {
            if (u == i)
                continue;
            int V = matrixG[u][i];
            int first_ = Flow.Get(u, i);
            int second_ = Flow.Get(i, u);
            int third_ = matrixG[i][u];
            if (!visited[i] && ((V != first_) || ((third_ != second_) && (second_ != 0))))
            {
                queue.push_back(i);
                visited[i] = true;
                level[i] = level[u] + 1;
            }
        }
    }
    int Max = level[dimG - 1];
    path->push_front(dimG - 1);
    while (Max != 0 && Max >= 0)
    {
        for (int j = 0; j < dimG; ++j)
        {
            int V = matrixG[j][path->what_at(0)];
            int first_ = Flow.Get(j, path->what_at(0));
            int second_ = Flow.Get(path->what_at(0), j);
            int third_ = matrixG[path->what_at(0)][j];
            if ((level[j] == Max - 1) && ((V != first_) || ((third_ != second_) && (second_ != 0))))
            {
                if (level[j] == Max - 1)
                {
                    path->push_front(j);
                    Max--;
                    break;
                }
            }
        }
    }
    delete[] level;
    delete[] visited;
    return path;
}

// Search for unique vertices in file 
void ReadFileAndTakeNames(string& names, int& numOfV, ifstream& file)
{
    char temp = ' ';
    while (!file.eof())
    {
        temp = file.get();
        if (temp == ' ' || isdigit(temp) || temp == '\n')       // we should skip it here
            continue;
        if (!isdigit(temp))                                     // getline gives us "V U 3", we need V and U
        {
            for (int i = 0; i < numOfV; ++i)
            {
                if (names[i] == temp)
                {
                    temp = ' ';
                    break;
                }
            }
            if (temp == ' ')
                continue;
            else
            {
                names += temp;
                numOfV++;
            }
        }
    }
}

// Now we are making a capacity matrix from a file
void SearchCapacity(int Vs, Graph* Capacity, char* names, ifstream& file)
{
    char temp = ' ';
    unsigned from = 0, to = 0;
    string temp_number;
    while (!file.eof())
    {
        temp_number = "";
        temp = file.get();
        if ((temp == '\n') || (temp == ' '))
            continue;
        else if (!isdigit(temp))
        {
            for (int i = 0; i < Vs; ++i)
            {
                if (names[i] == temp)
                    from = i;           // it's an analog for ReadFile() from Lab3
            }
            temp = file.get();          // spacebar
            temp = file.get();
            for (int i = 0; i < Vs; ++i)
            {
                if (names[i] == temp)
                    to = i;             // it's an analog for ReadFile() from Lab3
            }
        }
        else if (isdigit(temp))
        {
            temp_number.push_back(temp);        // we can't do (string_var + char_var) so we need some standard methods
            while (isdigit(temp = file.get()))          // in case if there's a number >10
                temp_number.push_back(temp);

            Capacity->Set(from, to, atoi(temp_number.c_str()));     // capasity->matrixG[from][to] = number
            if (file.eof())
                break;
        }
    }
}

void SortBetweenSandT(int names_size, char* names)
{   
    // S is always start, T is always end
    // but we should sort all between this two
    for (int i = 0; i < names_size - 1; ++i)
    {
        for (int j = 0; j < names_size - 1; ++j)
        {
            if ((names[j] > names[j + 1]) && (names[j] != 'S') && (names[j + 1] != 'T'))
            {
                char temp = names[j];
                names[j] = names[j + 1];
                names[j + 1] = temp;
            }
        }
    }
}

// The main algorithm of program
unsigned EdKaAlgo(int Vs, Graph& Capa)
{
    Graph* pathFlow = new Graph(Vs);
    unsigned toFindMaxFlow = 0;
    ListL2<int>* Path = new ListL2<int>();
    Path = Capa.BFS(*pathFlow);        // the best way, found by bfs

    int* Remainder = new int[Path->give_size() - 1];
    while (!(Path->isEmpty()) || (Path->give_size() >= 1))
    {
        Path = Capa.BFS(*pathFlow);
        Remainder = new int[Path->give_size() - 1];
        if ((Path->isEmpty()) || (Path->give_size() == 1))
            break;
        for (int i = 0; i < Path->give_size() - 1; ++i)
        {
            unsigned to = Capa.Get(Path->what_at(i), Path->what_at(i + 1));
            //looking for an edge with minimum bandwidth in the residual network
            unsigned from = Capa.Get(Path->what_at(i + 1), Path->what_at(i));
            if (to != 0)
                Remainder[i] = to - pathFlow->Get(Path->what_at(i), Path->what_at(i + 1));
            else if (from != 0)
                Remainder[i] = pathFlow->Get(Path->what_at(i + 1), Path->what_at(i));
            else
                Remainder = 0;
        }
        //looking for a minimum bandwidth in the residual network
        unsigned minCapa = Remainder[0];
        for (int i = 1; i < Path->give_size() - 1; i++)
            if (Remainder[i] < minCapa)
                minCapa = Remainder[i];
        // minCapa is the minimum bandwidth in the residual network
        for (int i = 0; i < Path->give_size() - 1; i++)
        {
            // counting new bandwidths
            unsigned to = pathFlow->Get(Path->what_at(i), Path->what_at(i + 1));
            unsigned from = pathFlow->Get(Path->what_at(i + 1), Path->what_at(i));
            if (from == 0)
                pathFlow->Set(Path->what_at(i), Path->what_at(i + 1), to + minCapa);
            else
                pathFlow->Set(Path->what_at(i + 1), Path->what_at(i), from - minCapa);
        }
    }
    for (int i = 0; i < Vs; i++)
    {
        if (pathFlow->Get(0, i) != 0)
            toFindMaxFlow += pathFlow->Get(0, i);
    }
    delete Path;
    delete pathFlow;
    delete[] Remainder;
    return toFindMaxFlow;
}

void Summing(unsigned& MaxFlow)
{
    int VNum = 0;
    ifstream file;
    file.open("task.txt");
    string tempStr = "";
    ReadFileAndTakeNames(tempStr, VNum, file);
    VNum = VNum - 1;
    char* names = new char[VNum];
    for (int k = 0; k < VNum; ++k)
        names[k] = tempStr[k];
    SortBetweenSandT(VNum, names);
    file.clear();
    file.seekg(0, ios::beg);
    Graph* Throughput = new Graph(VNum);
    SearchCapacity(VNum, Throughput, names, file);
    MaxFlow = EdKaAlgo(VNum, *Throughput);
    delete Throughput;
    delete[] names;
}