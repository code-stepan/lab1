#include <iostream>

using namespace std;

class logical_values_array {
private:
	unsigned int value;
public:
	logical_values_array(unsigned int _value = 0);
	void accessor() const;
	void inv();
	void con(logical_values_array& obj);
	void dis(logical_values_array& obj);
	void imp(logical_values_array& obj);
	void coimp(logical_values_array& obj);
	void sum2(logical_values_array& obj);
	void eqv(logical_values_array& obj);
	void pier_arrow(logical_values_array& obj);
	void strokes(logical_values_array& obj);
	static bool equals(logical_values_array& obj1, logical_values_array& obj2);
	bool get_bit(unsigned int position) const;
	void c10toi2(char* str);
};

int main() {
	logical_values_array o1(10), o2(7), o3;
	char* ptr = nullptr;
	o1.c10toi2(ptr);
	return 0;
}

logical_values_array::logical_values_array(unsigned int _value) {
	value = _value;
}

void logical_values_array::accessor() const {
	cout << value << endl;
}

void logical_values_array::inv() {
	value = ~value;
}

void logical_values_array::con(logical_values_array& obj) {
	value = value & obj.value;
}

void logical_values_array::dis(logical_values_array& obj) {
	value = value | obj.value;
}

void logical_values_array::imp(logical_values_array& obj) {
	value = (~value) | obj.value;
}

void logical_values_array::coimp(logical_values_array& obj) {
	value = ~((~value) | obj.value);
}

void logical_values_array::sum2(logical_values_array& obj) {
	value = value ^ obj.value;
}

void logical_values_array::eqv(logical_values_array& obj) {
	value = (value & obj.value) | (~(value) & ~(obj.value));
}

void logical_values_array::pier_arrow(logical_values_array& obj) {
	value = ~(value | obj.value);
}

void logical_values_array::strokes(logical_values_array& obj) {
	value = ~(value & obj.value);
}

bool logical_values_array::equals(logical_values_array& obj1, logical_values_array& obj2) {
	return obj1.value == obj2.value;
}

bool logical_values_array::get_bit(unsigned int position) const {
	return (value & (1 << position)) >> position;
}

void logical_values_array::c10toi2(char* res) {
	
}
