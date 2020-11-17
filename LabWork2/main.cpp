#include "LabWork2.h"
#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	int* array;
	int n = 10;
	array = new int[n];
	for (int i = 0; i < n; i++)
	{
		array[i] = rand();
	}
	BubbleSort(array, n);
	for (int i = 0; i < n; i++)
	{
		cout << array[i] << ' ';
	}
	cout << endl;
	clock_t time = 0;
	double time_array[10];
	double sum_time = 0;
	for (int i = 0; i < 5; i++)				// 10, 100, 1 000, 10 000, 100 000
	{
		for (int j = 0; j < 10; j++)
		{
			array = new int[n];
			for (int i = 0; i < n; i++)
			{
				array[i] = rand();
			}
			time = clock();
			QuickSort(array, 0, n - 1);
			time = clock() - time;
			time_array[j] = (double)time / CLOCKS_PER_SEC;
			cout << time_array[j] << endl;
			sum_time += time_array[j];
			delete[] array;
		}
		cout << "Average time: " << sum_time / 10 << endl;
		n = n * 10;
		sum_time = 0;
	}
	n = 10;
	for (int i = 0; i < 5; i++)				// 10, 100, 1 000, 10 000, 100 000
	{
		for (int j = 0; j < 10; j++)
		{
			array = new int[n];
			for (int i = 0; i < n; i++)
			{
				array[i] = rand();
			}
			time = clock();
			BubbleSort(array, n);
			time = clock() - time;
			time_array[j] = (double)time / CLOCKS_PER_SEC;
			cout << time_array[j] << endl;
			sum_time += time_array[j];
			delete[] array;
		}
		cout << "Average time: " << sum_time / 10 << endl;
		n = n * 10;
		sum_time = 0;
	}
	return 0;
}