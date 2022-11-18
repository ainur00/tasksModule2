// run-report https://contest.yandex.ru/contest/41792/run-report/75265764/

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

void Merge(std::vector<int>& v, int l, int m, int r, std::int64_t& inversionCount) {
    std::vector<int> result(r - l);
    int i = l;
    int j = m;
    while (i < m && j < r) {
        if (!(v[j] < v[i])) {
            result[i - l + j - m] = v[i];
            ++i;
        }
        else {
            result[i - l + j - m] = v[j];
            ++j;
            // прибавляем количество инверсий, так как здесь v[j] < v[i] и i < j.
            inversionCount += m - i;
        }
    }
    for (; i < m; ++i)
        result[i - l + j - m] = v[i];
    for (; j < r; ++j)
        result[j - l] = v[j];
    for (int k = 0; k < result.size(); ++k)
        v[l + k] = result[k];
}


void MergeSort(std::vector<int>& v, int l, int r, std::int64_t& inversionCount) {
    if (r - l <= 1)
        return;
    int med = (r + l) / 2;
    MergeSort(v, l, med, inversionCount);
    MergeSort(v, med, r, inversionCount);
    Merge(v, l, med, r, inversionCount);
}

void MergeSort(std::vector<int>& v, std::int64_t& inversionCount) {
    MergeSort(v, 0, v.size(), inversionCount);
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
