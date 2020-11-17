#include "LabWork2.h"
#include <iostream>

using namespace std;

bool isSorted(int array[], int n)
{
	int index = 0;
	do
	{
		if (array[index] > array[index + 1])
			return false;
		index++;
	}
	while (index != n-1);
	return true;
}

bool isSorted(char array[], int n)
{
	int index = 0;
	do
	{
		if (array[index] > array[index + 1])
			return false;
		index++;
	}
	while (index != n - 1);
	return true;
}

void BogoSort(int array[], int n)
{
	while (!isSorted(array, n))
	{
		for (int i = 0; i < n; i++)
			swap(array[i], array[rand() % n]);
	}
}

void BubbleSort(int array[], int n)
{
	for (int i = 0; i < n-1; i++)
		for (int j = n-2; j >= i; j--)
		{
			if (array[j] > array[j+1])
				swap(array[j], array[j+1]);
		}
}

void QuickSort(int array[], int low, int high)
{
	if (low >= high)
		return;					// sort is done
	int left = low, right = high, pivot = array[(low+high)/2];
	while (left <= right)
	{
		while (array[left] < pivot)
			left++;
		while (array[right] > pivot)
			right--;
		if (left <= right)
		{
			swap(array[left], array[right]);
			left++;
			right--;
		}
	}
	QuickSort(array, low, right);
	QuickSort(array, left, high);
}

void BinarySearch(int array[], int toFind, int n)
{
	int left = 0, right = n, current;
	while (left < right - 1)
	{
		current = (left + right) / 2;
		if (toFind < array[current])
			right = current;
		else
			left = current;
	}
	if (array[left] == toFind)
		cout << "Found: A[" << left << "] = " << toFind << endl;
	else
		cout << "Not found" << endl;
}

void CountingSort(char array[], int n)
{
	int i = 0, j = 0, max = 0;
	for (i = 0; i < n; i++)
	{
		if (max < int(array[i]))
			max = int(array[i]);
	}
	int* count = new int[max + 1];
	for (i = 0; i <= max; i++)
		count[i] = 0;
	for (i = 0; i < n; i++)
		count[int(array[i])]++;
	while (i <= max)
	{
		while (count[i] != 0)
		{
			array[j] = char(i);
			count[i]--;
			j++;
		}
		i++;
	}
}