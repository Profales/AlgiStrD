#include <iostream>
#include "GraphsAndStuff.h"
using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Добрый день!" << endl;
	cout << "В данной программе считается максммальный поток в транспортной сети." << endl;
	unsigned MaxFlow = 0;
	Summing(MaxFlow);
	cout << "Максимальный поток в транспортной сети равен: " << MaxFlow << endl;
    return 0;
}
