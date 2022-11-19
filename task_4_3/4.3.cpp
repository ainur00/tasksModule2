// run-report https://contest.yandex.ru/contest/41792/run-report/75301507/

/*
Дана последовательность целых чисел из диапазона (-1000000000 .. 1000000000).
Длина последовательности не больше 1000000. Числа записаны по одному в строке.
Количество чисел не указано.
Пусть количество элементов n, и числа записаны в массиве a = a[i]: i из [0..n-1].
Требуется напечатать количество таких пар индексов (i,j) из [0..n-1], что (i < j и a[i] > a[j]).
Указание: количество инверсий может быть больше 4*1000000000 - используйте int64_t.
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <cstdint>

void Merge(std::vector<int>& arr, int leftLimit, int median, int rightLimit, std::int64_t& inversionCount) {
    std::vector<int> result(rightLimit - leftLimit);
    int i = leftLimit;
    int j = median;
    while (i < median && j < rightLimit) {
        if (!(arr[j] < arr[i])) {
            result[i - leftLimit + j - median] = arr[i];
            ++i;
        }
        else {
            result[i - leftLimit + j - median] = arr[j];
            ++j;
            // прибавляем количество инверсий, так как здесь v[j] < v[i] и i < j.
            inversionCount += median - i;
        }
    }
    for (; i < median; ++i)
        result[i - leftLimit + j - median] = arr[i];
    for (; j < rightLimit; ++j)
        result[j - leftLimit] = arr[j];
    for (int k = 0; k < result.size(); ++k)
        arr[leftLimit + k] = result[k];
}


void MergeSort(std::vector<int>& arr, int leftLimit, int rightLimit, std::int64_t& inversionCount) {
    if (rightLimit - leftLimit <= 1)
        return;
    int med = (rightLimit + leftLimit) / 2;
    MergeSort(arr, leftLimit, med, inversionCount);
    MergeSort(arr, med, rightLimit, inversionCount);
    Merge(arr, leftLimit, med, rightLimit, inversionCount);
}

void MergeSort(std::vector<int>& arr, std::int64_t& inversionCount) {
    MergeSort(arr, 0, arr.size(), inversionCount);
}


std::int64_t GetInversionCount(std::vector<int> arr) {
    std::int64_t inversionCount = 0;
    MergeSort(arr, inversionCount);
    return inversionCount;
}


int main() {
    std::vector<int> arr;
    int x = 0;
    while (std::cin >> x)
        arr.push_back(x);

    std::int64_t inversionCount = GetInversionCount(arr);

    std::cout << inversionCount;
}
