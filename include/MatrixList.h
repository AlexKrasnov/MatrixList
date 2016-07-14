#pragma once
#include "ListElement.h"

// класс разреженной матрицы
class MatrixList
{
	ListElement* head; // заголовок списка
	int m,n; // размеры матрицы
	int count; // количество ненулевых элементов матрицы
public:
	MatrixList(int, int); // конструктор разреженной матрицы
	MatrixList(const MatrixList&); // конструктор копирования
	~MatrixList(); // деструктор матрицы
	void DestroyList(); // метод уничтожения списка элементов матрицы
	void AddElement(int, int, double); // метод добавления нового элемента в список
	void DeleteElement(int, int); // метод удаления элемента из списка
	MatrixList operator + (MatrixList&); // оператор сложения двух матриц
	MatrixList operator = (MatrixList&); // оператор присваивания матрицы
	// метод проверки, является ли матрица трехдиагональной
	bool IsTripleDiagonal();
	// метод получения элемента матрицы с заданными индексами
	ListElement* ExistsElement(int, int);
	friend ostream& operator << (ostream& out, MatrixList& ob)
	{
		int i1 = 0, j1 = 0;
		// цикл просмотра элементов списка
		ListElement* current = ob.head;
		while(current != NULL)
		{
			// вывод нулей в качестве элементов
			// предшествующих строк
			for( ; i1 < current->GetElement().GetIndex1(); i1++)
			{
				for( ; j1 < ob.n; j1++)
					out << "0\t";
				out << endl;
				j1 = 0;
			}
			// вывод нулей в качестве элементов в той же строке,
			// но в прешествующих столбцах
			for( ;j1 < current->GetElement().GetIndex2(); j1++)
				out << "0\t";
			// вывод текущего элемента
			out << *current << "\t";
			// корректировка индексов для просмотра
			// следующих элементов
			j1++;
			if(j1 == ob.n)
			{
				i1++;
				j1 = 0;
				out << endl;
			}
			current = current->GetNext();
		}
		// вывод нулей в качестве последующих элементов
		// строки, в которой расположен
		// последний элемент списка
		if(j1 != 0)
		{
			for( ; j1 < ob.n; j1++)
				out << "0\t";
			out << endl;
			i1++;
		}
		// вывод нулей в качестве элементов строк,
		// расположенных после той,
		// в которой находится последний элемент списка
		for( ;i1 < ob.m; i1++)
		{
			for(j1 = 0; j1 < ob.n; j1++)
				out << "0\t";
			out << endl;
		}
		return out;
	}
};