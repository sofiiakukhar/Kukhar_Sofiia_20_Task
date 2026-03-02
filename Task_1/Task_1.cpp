#include <iostream>
#include <chrono>
#include <future>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;
using namespace chrono;
void generateArray(int* arr, int n)
{
	for (int i = 0; i < n; i++)
		arr[i] = rand() % 10000;
}
void copyArray(int* source, int* dest, int n)
{
	for (int i = 0; i < n; i++)
		dest[i] = source[i];
}
void printArray(int* arr, int n)
{
	int limit = (n > 20) ? 20 : n;
	for (int i = 0; i < limit; i++)
		cout << arr[i] << " ";
	if (n > 20)
		cout << "...";
	cout << endl;
}
void bubbleSort(int* arr, int n)
{
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1])
				swap(arr[j], arr[j + 1]);
}
void selectionSort(int* arr, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < n; j++)
			if (arr[j] < arr[minIndex])
				minIndex = j;
		swap(arr[i], arr[minIndex]);
	}
}
int partition(int* arr, int low, int high)
{
	int pivot = arr[high];
	int i = low - 1;
	for (int j = low; j < high; j++)
	{
		if (arr[j] < pivot)
		{
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return i + 1;
}
void quickSort(int* arr, int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}
void quickWrapper(int* arr, int n)
{
	quickSort(arr, 0, n - 1);
}
long long measureSync(void(*sortFunc)(int*, int), int* arr, int n)
{
	auto start = high_resolution_clock::now();
	sortFunc(arr, n);
	auto stop = high_resolution_clock::now();
	return duration_cast<microseconds>(stop - start).count();
}
long long measureAsync(void(*sortFunc)(int*, int), int* arr, int n)
{
	auto start = high_resolution_clock::now();
	auto fut = async(launch::async, sortFunc, arr, n);
	fut.get();
	auto stop = high_resolution_clock::now();
	return duration_cast<microseconds>(stop - start).count();
}
int binarySearch(int* arr, int n, int key)
{
	int left = 0;
	int right = n - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (arr[mid] == key)
			return mid;
		if (arr[mid] < key)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return -1;
}
int main()
{
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
	srand(time(0));
	int sizes[6] = { 8, 80, 1200, 4000, 25000, 100000 };
	int repeats = 5;
	for (int s = 0; s < 6; s++)
	{
		int n = sizes[s];
		cout << "\n============================\n";
		cout << "N = " << n << endl;

		int* original = new int[n];
		int* arr1 = new int[n];
		int* arr2 = new int[n];
		int* arr3 = new int[n];
		int* sortedArray = new int[n];
		generateArray(original, n);
		cout << "Початковий масив:\n";
		printArray(original, n);
		long long totalBubbleSync = 0;
		long long totalSelectionSync = 0;
		long long totalQuickSync = 0;
		long long totalBubbleAsync = 0;
		long long totalSelectionAsync = 0;
		long long totalQuickAsync = 0;
		for (int r = 0; r < repeats; r++)
		{
			copyArray(original, arr1, n);
			copyArray(original, arr2, n);
			copyArray(original, arr3, n);
			totalBubbleSync += measureSync(bubbleSort, arr1, n);
			totalSelectionSync += measureSync(selectionSort, arr2, n);
			totalQuickSync += measureSync(quickWrapper, arr3, n);
			if (r == repeats - 1)
				copyArray(arr3, sortedArray, n);
			copyArray(original, arr1, n);
			copyArray(original, arr2, n);
			copyArray(original, arr3, n);
			totalBubbleAsync += measureAsync(bubbleSort, arr1, n);
			totalSelectionAsync += measureAsync(selectionSort, arr2, n);
			totalQuickAsync += measureAsync(quickWrapper, arr3, n);
		}
		cout << "Bubble Sync (avg): " << totalBubbleSync / repeats << " мкс\n";
		cout << "Selection Sync (avg): " << totalSelectionSync / repeats << " мкс\n";
		cout << "Quick Sync (avg): " << totalQuickSync / repeats << " мкс\n";
		cout << "Bubble Async (avg): " << totalBubbleAsync / repeats << " мкс\n";
		cout << "Selection Async (avg): " << totalSelectionAsync / repeats << " мкс\n";
		cout << "Quick Async (avg): " << totalQuickAsync / repeats << " мкс\n";
		cout << "Відсортований масив:\n";
		printArray(sortedArray, n);
		int key;
		cout << "\nВведіть елемент для пошуку: ";
		cin >> key;
		int result = binarySearch(sortedArray, n, key);
		if (result != -1)
			cout << "Елемент знайдено на позиції: " << result << endl;
		else
			cout << "Елемент не знайдено\n";
		delete[] original;
		delete[] arr1;
		delete[] arr2;
		delete[] arr3;
		delete[] sortedArray;
	}
	return 0;
}


