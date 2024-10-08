// run-report https://contest.yandex.ru/contest/41792/run-report/75516694/

/*
В супермаркете решили оптимизировать показ рекламы.
Известно расписание прихода и ухода покупателей (два целых числа).
Каждому покупателю необходимо показать минимум 2 рекламы.
Рекламу можно транслировать только в целочисленные моменты времени.
Покупатель может видеть рекламу от момента прихода до момента ухода из магазина.
В каждый момент времени может показываться только одна реклама.
Считается, что реклама показывается мгновенно.
Если реклама показывается в момент ухода или прихода, то считается, что посетитель успел её посмотреть.
Требуется определить минимальное число показов рекламы.
*/

#include <iostream>
#include <vector>
#include <queue>

struct Buyer {
	int comingTime;
	int leavingTime;
};

bool CompareByLeavingTime(const Buyer& buyer1, const Buyer& buyer2) {
	if (buyer1.leavingTime != buyer2.leavingTime)
		return (buyer1.leavingTime < buyer2.leavingTime);
	else
		return (buyer1.comingTime > buyer2.comingTime);
}

void SiftDown(std::vector<Buyer>& arr, int heapSize, int i, bool (*compareFunction)(const Buyer&, const Buyer&)) {
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int largest = i;
	if (left < heapSize && !compareFunction(arr[left], arr[i]))
		largest = left;
	if (right < heapSize && !compareFunction(arr[right], arr[largest]))
		largest = right;
	if (largest != i) {
		std::swap(arr[i], arr[largest]);
		SiftDown(arr, heapSize, largest, compareFunction);
	}
}

void BuildHeap(std::vector<Buyer>& arr, bool (*compareFunction)(const Buyer&, const Buyer&)) {
	for (int i = arr.size() / 2 - 1; i >= 0; --i)
		SiftDown(arr, arr.size(), i, compareFunction);
}

void HeapSort(std::vector<Buyer>& arr, bool (*compareFunction)(const Buyer&, const Buyer&)) {
	int heapSize = arr.size();
	BuildHeap(arr, compareFunction);
	while (heapSize > 1) {
		std::swap(arr[0], arr[heapSize - 1]);
		heapSize--;
		SiftDown(arr, heapSize, 0, compareFunction);
	}
}

int GetAdImpressionMinCount(std::vector<Buyer>& buyers) {
	if (buyers.size() == 0)
		return 0;
	HeapSort(buyers, CompareByLeavingTime);
	// по условию задачи если есть хоть 1 покупатель, значит ему нужно показать минимум 2 рекламы, значит моменты времени {buyers[0].leavingTime} и {buyers[0].leavingTime - 1} существуют.
	std::queue<int> lastTwoAdTime;
	// сразу добавим количество реклам 2 и время этих реклам
	lastTwoAdTime.push(buyers[0].leavingTime - 1);
	lastTwoAdTime.push(buyers[0].leavingTime);
	int adCount = 2;
	// рассматриваем случаи: если обе последние рекламы были показаны после прихода и до ухода i-го покупателя, только последняя попала в этот промежуток, ни одна из этих реклам не попала в этот промежуток
	for (int i = 1; i < buyers.size(); ++i) {
		if ((lastTwoAdTime.back() >= buyers[i].comingTime) && (lastTwoAdTime.front() >= buyers[i].comingTime))
			continue;
		else if (lastTwoAdTime.back() >= buyers[i].comingTime) {
			lastTwoAdTime.pop();
			lastTwoAdTime.push(buyers[i].leavingTime);
			adCount++;
		}
		else {
			lastTwoAdTime.pop();
			lastTwoAdTime.pop();
			lastTwoAdTime.push(buyers[i].leavingTime - 1);
			lastTwoAdTime.push(buyers[i].leavingTime);
			adCount += 2;
		}
	}
	return adCount;
}

int main() {
	int buyerCount = 0;
	std::cin >> buyerCount;
	std::vector<Buyer> buyers(buyerCount);
	for (int i = 0; i < buyerCount; ++i)
		std::cin >> buyers[i].comingTime >> buyers[i].leavingTime;

	std::cout << GetAdImpressionMinCount(buyers);

	return 0;
}

