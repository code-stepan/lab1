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
	// matrix reverse();
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
		cout << "—ложить матрицы невозможно." << endl;
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
		cout << "”множить матрицы невозможно." << endl;
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
		cout << "¬ычитать матрицы невозможно." << endl;
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
	det = d;
	return d;
}

void matrix::transposition() {
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			swap(elements[i][j], elements[j][i]);
		}
	}
}

// м-да...
//matrix matrix::reverse() {
//	matrix res = *this;
//	for (int i = 0; i < n; i++) {
//		for (int j = 0; j < n; j++) {
//			if ((i + j) % 2 == 1) res.elements[i][j] = -elements[i][j];
//			else res.elements[i][j] = elements[i][j];
//		}
//	}
//}

// м-да... x2 // может "()" перегрузить?)
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

	return 0;
}