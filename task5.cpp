#include <iostream>
#include <vector>

using namespace std;

class Heap {
private:
	vector<int> a;

	void up(int i) { // Принимает индекс элемента, который нужно поднять
		while (i != 0 && a[i] > a[(i - 1) / 2]) {
			swap(a[i], a[(i - 1) / 2]);
			i = (i - 1) / 2;
		}
	}

	void down(int i) {
		while (2 * i + 1 < a.size()) { // пока не стали листом
			// лпределяем индекс максимального ребенка
			int maxChild = 2 * i + 1;
			if (maxChild + 1 < a.size() && a[maxChild] < a[maxChild + 1]) maxChild++;

			if (a[i] >= a[maxChild])
				break;

			swap(a[i], a[maxChild]);
			i = maxChild;
		}
	}

public:
	void push(int value) {
		a.push_back(value); // Добавляем элемент
		up(a.size() - 1); // Поднимаем его вверх
	}

	int pop() {
		int value = a[0];
		a[0] = a[a.size() - 1]; // ставим на первое место последний эелемент
		a.pop_back(); // выносим последний элемент
		down(0);
		return value;
	}
};

int main() {
	return 0;
}