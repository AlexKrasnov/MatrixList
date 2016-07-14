#pragma once
#include "MatrixElement.h"

// класс одного элемента списка
class ListElement
{
	MatrixElement a; // элемент матрицы
	ListElement* next; // следующий элемент списка
	friend class MatrixElement;
	friend class MatrixList;
public:
	// конструктор одного элемента списка
	ListElement(int i1, int j1 , double val) : a(i1,j1,val), next(NULL) {}
	MatrixElement GetElement() const { return a; }
	ListElement* GetNext() const { return next; }
	friend ostream& operator << (ostream& out, ListElement& ob)
	{
		out << ob.a;
		return out;
	}
};