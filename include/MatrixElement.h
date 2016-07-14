#pragma once
#include <iostream>

using namespace std;

class MatrixElement
{
	int i, j; // индексы элемента
	double value; // значение элемента
	friend class ListElement;
	friend class MatrixList;
public:
	MatrixElement(int i1, int j1, double val) : i(i1), j(j1), value(val) {}
	int GetIndex1() const { return i; }
	int GetIndex2() const { return j; }
	friend ostream& operator << (ostream& out, MatrixElement& ob)
	{
		out << ob.value;
		return out;
	}
};