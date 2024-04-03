#include <iostream>
#include <stdarg.h>
#include <cmath>

using namespace std;

class matrix {
private:
	double** elements;
	size_t n;
	double det;
public:
	matrix();
	matrix(int count, ...);
	matrix(matrix const& m);
	~matrix();
	void show() const;
	matrix& operator=(matrix const& m2);
	matrix operator+(matrix const& m);
	matrix operator*(matrix const& m);
	matrix operator*(double num);
	friend matrix operator*(double num, matrix const& m);
	matrix operator-(matrix const& m);
	// double* operator[](int index);
	double determinant();
	void transposition();
	matrix inverse() const;
};

matrix::matrix() {
	elements = nullptr;
	n = 0;
}

matrix::matrix(int count, ...) {
	n = sqrt(count);
	va_list va;
	va_start(va, count);
	elements = new double*[n];
	for (int i = 0; i < n; i++) {
		elements[i] = new double[n];
		for (int j = 0; j < n; j++) elements[i][j] = va_arg(va, double);
	}
	va_end(va);
}

matrix::matrix(matrix const& m) {
	n = m.n;
	elements = new double*[n];
	for (int i = 0; i < n; i++) {
		elements[i] = new double[n];
		for (int j = 0; j < n; j++) elements[i][j] = m.elements[i][j];
	}
}

matrix& matrix::operator=(matrix const& m) {
	for (int i = 0; i < n; i++) delete elements[i];
	delete[]elements;
	n = m.n;
	elements = new double* [n];
	for (int i = 0; i < n; i++) {
		elements[i] = new double[n];
		for (int j = 0; j < n; j++) elements[i][j] = m.elements[i][j];
	}
	return *this;
}

matrix::~matrix() {
	for (int i = 0; i < n; i++) delete elements[i];
	delete[]elements;
	//cout << " Des ...";
}

void matrix::show() const {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) cout << elements[i][j] << "\t";
		cout << endl;
	}
}

matrix matrix::operator+(matrix const& m) {
	matrix tmp = *this;
	if (n != m.n) {
		cout << "Сложить матрицы невозможно." << endl;
	}
	else {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				tmp.elements[i][j] += m.elements[i][j];
	}
	return tmp;
}

matrix matrix::operator*(matrix const& m) {
	matrix tmp = *this;
	if (n != m.n) {
		cout << "Умножить матрицы невозможно." << endl;
	}
	else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				tmp.elements[i][j] = 0;
				for (int k = 0; k < n; k++) {
					tmp.elements[i][j] += elements[i][k] * m.elements[k][j];
				}
			}
		}
	}
	return tmp;
}

matrix matrix::operator*(double num) {
	matrix tmp = *this;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) tmp.elements[i][j] *= num;
	}
	return tmp;
}

matrix operator*(double num, matrix const& m) {
	matrix tmp = m;
	for (int i = 0; i < tmp.n; i++) {
		for (int j = 0; j < tmp.n; j++) tmp.elements[i][j] *= num;
	}
	return tmp;
}

matrix matrix::operator-(matrix const& m) {
	matrix tmp = *this;
	if (n != m.n) {
		cout << "Вычитать матрицы невозможно." << endl;
	}
	else {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				tmp.elements[i][j] -= m.elements[i][j];
	}
	return tmp;
}

double matrix::determinant() {
	matrix m = *this;
	size_t n = m.n;
	double d = 1;
	for (size_t i = 0; i < n; ++i) {
		double pivotElement = m.elements[i][i];
		size_t pivotRow = i;
		for (size_t row = i + 1; row < n; ++row) {
			if (abs(m.elements[row][i]) > abs(pivotElement)) {
				pivotElement = m.elements[row][i];
				pivotRow = row;
			}
		}
		if (pivotElement == 0) return 0;
		if (pivotRow != i) {
			swap(m.elements[i], m.elements[pivotRow]);
			d *= -1;
		}
		d *= pivotElement;
		for (size_t row = i + 1; row < n; ++row) {
			for (size_t col = i + 1; col < n; ++col)
				m.elements[row][col] -= m.elements[row][i] * m.elements[i][col] / pivotElement;
		}
	}

	return d;
}

void matrix::transposition() {
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			swap(elements[i][j], elements[j][i]);
		}
	}
}

matrix matrix::inverse() const {
	matrix temp = *this; // Копия прошлой матрицы
	matrix identity = *this; // Единичная матрица
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			identity.elements[i][j] = 0;
		}
	}
	for (int i = 0; i < n; i++) {
		identity.elements[i][i] = 1.0;
	}

	for (size_t i = 0; i < n; i++) {
		size_t pivot_row = i;
		for (size_t j = i + 1; j < n; j++) {
			if (abs(temp.elements[j][i]) > abs(temp.elements[pivot_row][i])) {
				pivot_row = j;
			}
		}

		if (pivot_row != i) {
			for (size_t j = 0; j < n; j++) {
				swap(temp.elements[i][j], temp.elements[pivot_row][j]);
				swap(identity.elements[i][j], identity.elements[pivot_row][j]);
			}
		}

		double pivot = temp.elements[i][i];
		for (size_t j = 0; j < n; j++) {
			temp.elements[i][j] /= pivot;
			identity.elements[i][j] /= pivot;
		}

		for (size_t k = 0; k < n; k++) {
			if (k != i) {
				double factor = temp.elements[k][i];
				for (size_t j = 0; j < n; j++) {
					temp.elements[k][j] -= factor * temp.elements[i][j];
					identity.elements[k][j] -= factor * identity.elements[i][j];
				}
			}
		}
	}
	return identity;
}

// м-да... // может "()" перегрузить?)))
//double* matrix::operator[](int index) {
//	return elements[index];
//}

int main()
{
	system("chcp 1251>nul");
	matrix a(9, 1.9, 2.7, 3.4, 4.3, 5.7, 6.4, 7.8, 8.1, 9.2);
	matrix b(a), c;
	a.show(); cout << endl;
	b.show(); cout << endl;

	c = 2 * (a * 2);
	c.show(); cout << endl;

	c = c - a;
	c.show(); cout << endl;
	cout << a.determinant() << endl;
	a.transposition();
	a.show(); cout << endl;
	
	c = a.inverse();
	c.show();
	return 0;
}