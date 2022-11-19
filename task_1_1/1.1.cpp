// посылка https://contest.yandex.ru/contest/41792/run-report/75261497/

/*
На склад привезли много пустых ящиков. Все ящики пронумерованы по порядку поступления от 0.
Известно, что их все можно сложить один в один(то есть так, что каждый следующий помещается в предыдущий).
Один ящик можно вложить в другой, если его можно перевернуть так, что размеры одного ящика по всем осям станут строго меньше размеров другого ящика по соответствующим осям.
Требуется определить, в какой последовательности они будут вложены друг в друга.
Вывести номера ящиков.
Максимальное кол - во 10000.
*/

#include <iostream>
#include <vector>

struct Box {
	int index;
	int xSize;
	int ySize;
	int zSize;
};

void InsertionSort(std::vector<Box>& boxes, bool (*compareFunction)(const Box&, const Box&)) {
	for (int i = 1; i < boxes.size(); ++i) {
		Box boxI = boxes[i];
		int j = i - 1;
		for (; j >= 0 && compareFunction(boxI, boxes[j]); --j)
			boxes[j + 1] = boxes[j];
		boxes[j + 1] = boxI;
	}
}

// сравниваем все возможные повороты коробки
bool CompareBySize(const Box& box1, const Box& box2) {
	if (((box1.xSize < box2.xSize) && (box1.ySize < box2.ySize) && (box1.zSize < box2.zSize)) ||
		((box1.xSize < box2.xSize) && (box1.zSize < box2.ySize) && (box1.ySize < box2.zSize)) ||
		((box1.ySize < box2.xSize) && (box1.xSize < box2.ySize) && (box1.zSize < box2.zSize)) ||
		((box1.ySize < box2.xSize) && (box1.zSize < box2.ySize) && (box1.xSize < box2.zSize)) ||
		((box1.zSize < box2.xSize) && (box1.ySize < box2.ySize) && (box1.xSize < box2.zSize)) ||
		((box1.zSize < box2.xSize) && (box1.xSize < box2.ySize) && (box1.ySize < box2.zSize)))
		return true;
	else
		return false;
}

int main() {
	int boxCount = 0;
	std::cin >> boxCount;
	std::vector<Box> boxes(boxCount);
	for (int i = 0; i < boxCount; ++i) {
		int iBoxXSize = 0;
		int iBoxYSize = 0;
		int iBoxZSize = 0;
		std::cin >> iBoxXSize >> iBoxYSize >> iBoxZSize;
		boxes[i].index = i;
		boxes[i].xSize = iBoxXSize;
		boxes[i].ySize = iBoxYSize;
		boxes[i].zSize = iBoxZSize;
	}

	InsertionSort(boxes, CompareBySize);

	for (int i = 0; i < boxCount; ++i)
		std::cout << boxes[i].index << std::endl;
}

