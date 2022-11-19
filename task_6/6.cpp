// run-report https://contest.yandex.ru/contest/42399/run-report/75301877/

/*
Дан массив целых чисел в диапазоне [0..109]. 
Размер массива кратен 10 и ограничен сверху значением 2.5 * 107 элементов. 
Все значения массива являются элементами псевдо-рандомной последовательности. 
Необходимо написать функцию сортировки массива.
Для этого нужно прислать .cpp файл, в котором описать функцию Sort
void Sort(unsigned int* arr, unsigned int size);
Необходимо включить в файл header #include "sort.h"
*/

#include "sort.h"

#include <stack>
#include <iostream>
#include <vector>
#include <random>

// открытый справа и замкнутый слева полуинтервал [a; b)
struct HalfInterval {
	HalfInterval(int leftL, int rightL) {
		leftLimit = leftL;
		rightLimit = rightL;
		elementCountInHalfInterval = rightL - leftL;
	}
	int leftLimit;
	int rightLimit;
	int elementCountInHalfInterval;
};

int GetMidNumIndex(unsigned int* arr, int num1Index, int num2Index, int num3Index) {
	int midNum = arr[num1Index] + arr[num2Index] + arr[num3Index] - std::max(arr[num1Index], std::max(arr[num2Index], arr[num3Index])) - std::min(arr[num1Index], std::min(arr[num2Index], arr[num3Index]));
	if (arr[num1Index] == midNum)
		return num1Index;
	if (arr[num2Index] == midNum)
		return num2Index;
	if (arr[num3Index] == midNum)
		return num3Index;
}

int GetRandomIntIndexInHalfInterval(HalfInterval halfInterval) {
	return halfInterval.leftLimit + std::rand() % (halfInterval.rightLimit - halfInterval.leftLimit);
}

// возвращает среднее и трех рандмоных чисел из диапазона halfInterval
int GetPivotPosition(unsigned int* arr, HalfInterval halfInterval) {
	return GetMidNumIndex(arr, GetRandomIntIndexInHalfInterval(halfInterval), GetRandomIntIndexInHalfInterval(halfInterval), GetRandomIntIndexInHalfInterval(halfInterval));
}

int Partition(unsigned int* arr, HalfInterval halfInterval) {
	if (halfInterval.rightLimit - halfInterval.leftLimit <= 1)
		return 0;
	int pivotPosition = GetPivotPosition(arr, halfInterval);
	std::swap(arr[pivotPosition], arr[halfInterval.rightLimit - 1]);
	int i = halfInterval.leftLimit;
	int j = halfInterval.rightLimit - 2;
	while (i <= j) {
		for (; arr[i] < arr[halfInterval.rightLimit - 1]; ++i);
		for (; j >= halfInterval.leftLimit && !(arr[j] < arr[halfInterval.rightLimit - 1]); --j);
		if (i < j)
			std::swap(arr[i++], arr[j--]);
	}
	std::swap(arr[i], arr[halfInterval.rightLimit - 1]);
	return i;
}

void InsertionSort(unsigned int* arr, HalfInterval halfInterval) {
	for (int i = halfInterval.leftLimit; i < halfInterval.rightLimit; ++i) {
		int tmp = arr[i];
		int j = i - 1;
		for (; (j >= 0) && (arr[j] > tmp); --j)
			arr[j + 1] = arr[j];
		arr[j + 1] = tmp;
	}
}


void Sort(unsigned int* arr, unsigned int arrSize) {
	if (arrSize <= 1)
		return;
	int leftLimit = 0;
	int rightLimit = arrSize;
	// стек для параметров
	std::stack<HalfInterval> quickSortParameters;
	HalfInterval arrIndexes(leftLimit, rightLimit);
	quickSortParameters.push(arrIndexes);
	while (!quickSortParameters.empty()) {
		HalfInterval anotherHalfInterval(quickSortParameters.top().leftLimit, quickSortParameters.top().rightLimit);
		quickSortParameters.pop();
		if (anotherHalfInterval.elementCountInHalfInterval <= 1)
			continue;
		else if (anotherHalfInterval.elementCountInHalfInterval <= 125)
		{
			// на маленьких размерах сортируем с помощью InsertionSort
			InsertionSort(arr, anotherHalfInterval);
			continue;
		}
		int pivotPosition = Partition(arr, anotherHalfInterval);
		HalfInterval leftHalfInterval(anotherHalfInterval.leftLimit, pivotPosition);
		quickSortParameters.push(leftHalfInterval);
		HalfInterval rightHalfInterval(pivotPosition + 1, anotherHalfInterval.rightLimit);
		quickSortParameters.push(rightHalfInterval);
	}
}

