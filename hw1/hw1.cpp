#include "stdafx.h"
#include <iostream>
#include <random>
#include <time.h>

using namespace std;

void heapify(int arr[], int n, int i)
{
	int largest = i; 
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && arr[l] > arr[largest])
		largest = l;

	if (r < n && arr[r] > arr[largest])
		largest = r;

	if (largest != i)
	{
		swap(arr[i], arr[largest]);

		heapify(arr, n, largest);
	}
}

void heapSort(int arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	for (int i = n - 1; i >= 0; i--)
	{
		swap(arr[0], arr[i]);

		heapify(arr, i, 0);
	}
}

void quickSort(int arr[], int left, int right) {

	int i = left, j = right;

	int tmp;

	int pivot = arr[(left + right) / 2];

	while (i <= j)
	{
		while (arr[i] < pivot)
		{
			i++;
		}
		while (arr[j] > pivot)
		{
			j--;
		}
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};

	if (left < j)
		quickSort(arr, left, j);

	if (i < right)
		quickSort(arr, i, right);
}

int main()
{
	srand(time(NULL));
	const int ARR_SIZE = 50;
	int* asd = new int[ARR_SIZE];
	for (size_t i = 0; i < ARR_SIZE; i++)
	{
		asd[i] = rand() % 100;
	}

	for (size_t i = 0; i < ARR_SIZE; i++)
	{
		std::cout << asd[i] << " ";
	}
	std::cout << std::endl;

	int beginning = 0;
	int end = ARR_SIZE-1;

	// Choose one of the sorts

	//quickSort(asd, beginning, end);
	//heapSort(asd, ARR_SIZE);

	for (size_t i = 0; i < ARR_SIZE; i++)
	{
		std::cout << asd[i] << " ";
	}

	return 0;
}
