// run-report https://contest.yandex.ru/contest/41792/run-report/75278258/

/*
Даны неотрицательные целые числа n, k и массив целых чисел из диапазона [0..109] размера n.
Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k из [0..n-1] в отсортированном массиве.
Напишите нерекурсивный алгоритм.
Требования к дополнительной памяти: O(n).
Требуемое среднее время работы: O(n).
Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
*/

#include <iostream>

int GetMidNumIndex(int* arr, int num1Index, int num2Index, int num3Index) {
	int midNum = arr[num1Index] + arr[num2Index] + arr[num3Index] - std::max(arr[num1Index], std::max(arr[num2Index], arr[num3Index])) - std::min(arr[num1Index], std::min(arr[num2Index], arr[num3Index]));
	if (arr[num1Index] == midNum)
		return num1Index;
	if (arr[num2Index] == midNum)
		return num2Index;
	if (arr[num3Index] == midNum)
		return num3Index;
}

int Partition(int* arr, int arrSize, int leftLimit, int rightLimit) {
	int leftNumIndex = leftLimit;
	int midNumIndex = (leftLimit + rightLimit) / 2;
	int rightNumIndex = rightLimit - 1;
	int pivotPosition = GetMidNumIndex(arr, leftNumIndex, midNumIndex, rightNumIndex);
	std::swap(arr[pivotPosition], arr[rightLimit - 1]);
	int i = leftLimit;
	int j = leftLimit;
	while (j != rightLimit - 1) {
		if (arr[j] > arr[rightLimit - 1])
			j++;
		else
			std::swap(arr[i++], arr[j++]);
	}
	std::swap(arr[i], arr[rightLimit - 1]);
	return i;
}

int GetKStat(int* arr, int arrSize, int k) {
	int leftLimit = 0;
	int rightLimit = arrSize;
	while (true) {
		int pivotPosition = Partition(arr, arrSize, leftLimit, rightLimit);
		if (pivotPosition == k)
			return arr[pivotPosition];
		if (pivotPosition < k)
			leftLimit = pivotPosition + 1;
		else
			rightLimit = pivotPosition;
	}
}

int main() {
	int arrSize = 0;
	int k = 0;
	std::cin >> arrSize >> k;
	int* arr = new int[arrSize];
	for (int i = 0; i < arrSize; ++i)
		std::cin >> arr[i];

	int kStat = GetKStat(arr, arrSize, k);

	std::cout << kStat;
}
