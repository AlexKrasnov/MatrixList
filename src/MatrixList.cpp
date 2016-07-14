#include "MatrixList.h"

// конструктор матрицы из нулевых элементов заданных размеров
MatrixList::MatrixList(int m1, int n1) : m(m1), n(n1), head(NULL), count(0) {}

// конструктор копирования матриц
MatrixList::MatrixList(const MatrixList& ob) : m(ob.m), n(ob.n)
{
	// создание списка элементов матрицы путем
	// поэлементного копирования из списка
	// элементов заданной матрицы ob
	if (ob.head == NULL)
	{
		head = NULL;
		return;
	}
	ListElement* current = ob.head->next;
	ListElement* current1;
	head = new ListElement(ob.head->a.i, ob.head->a.j,
		ob.head->a.value);
	head->next = NULL;
	count++;
	current1 = head;
	while(current != NULL)
	{
		current1->next = new ListElement(current->a.i,
			current->a.j, current->a.value);
		current1 = current1->next;
		current = current->next;
		count++;
	}
}

// операция присваивания матриц
MatrixList MatrixList::operator = (MatrixList& ob)
{
	// уничтожение списка, которому будет
	// присвоено новое значение
	DestroyList();
	// создание списка элементов матрицы путем
	// поэлементного копирования из списка
	// элементов заданной матрицы ob
	m = ob.m;
	n = ob.n;
	count = ob.count;
	if (ob.head == NULL)
	{
		head = NULL;
		return *this;
	}
	ListElement* current = ob.head->next;
	ListElement* current1;
	head = new ListElement(ob.head->a.i, ob.head->a.j, ob.head->a.value);
	head -> next = NULL;
	current1 = head;
	while(current != NULL)
	{
		current1 -> next = new ListElement(current->a.i, current->a.j, current->a.value);
		current1 = current1->next;
		current = current->next;
	}
	return *this;
}

// метод уничтожения списка
void MatrixList::DestroyList()
{
	ListElement* current = head, * help;
	while(current != NULL)
	{
		help = current->next;
		delete current;
		current = help;
	}
}

// деструктор матрицы
MatrixList::~MatrixList()
{
	DestroyList();
}

// метод добавления нового элемента в список –
// используется как метод присвоения
// элементу матрицы конкретного значения
void MatrixList::AddElement(int i, int j, double v)
{
	ListElement *current, *help, *prev;
	bool insert = false;
	// проверка корректности позиции
	// вставляемого элемента
	if (i < m && j < n)
	{
		// если новое значение элемента нулевое,
		// удаляем элемент из списка
		if(v == 0)
		{
			DeleteElement(i, j);
			return;
		}
		// проверка, вставляется ли элемент
		// на первое место
		if(head == NULL || i < head->a.i ||
			(i == head->a.i && j < head->a.j))
		{
			// вставка элемента в начало списка
			help = new ListElement(i, j, v);
			help->next = head;
			head = help;
			count++;
			return;
		}
		// поиск позиции вставляемого элемента
		prev = head;
		current = head -> next;
		// пропускаем элементы, находящиеся
		// в строках с меньшим номером
		while(current != NULL && i > current->a.i)
		{
			current = current->next;
			prev = prev->next;
		}
		if(current != NULL && i == current->a.i)
		{
			// пропускаем элементы, находящиеся в той же
			// строке,но в столбцах с меньшим номером
			while(current != NULL && j > current->a.j)
			{
				current = current->next;
				prev = prev->next;
			}
			// если элемент в заданной позиции уже
			// имеется,изменяем его значение
			if(current != NULL && j == current->a.j)
			{
				current->a.value = v;
				insert = true;
			}
		}
		// вставляем новый элемент в список
		if(!insert)
		{
			help = new ListElement(i, j, v);
			prev->next = help;
			help->next = current;
			count++;
		}
	}
	else throw "Неккоректная позиция вставляемого элемента";
}
// метод удаления элемента по индексам,
// т.е. присвоение элементу нулевого значения
void MatrixList::DeleteElement(int i, int j)
{
	ListElement* help, *prev, *current;
	// список пуст, следовательно, матрица нулевая
	if(head == NULL)
		return;
	// удаление первого элемента списка
	if(head->a.i == i && head->a.j == j)
	{
		help = head;
		head = head->next;
		delete help;
		return;
	}
	// поиск позиции в списке удаляемого элемента
	// и предшествующего ему
	prev = head;
	current = head->next;
	// пропускаем элементы, находящиеся
	// в строках с меньшим номером
	while(current != NULL && i > current->a.i)
	{
		current = current->next;
		prev = prev->next;
	}
	if(current != NULL && i == current->a.i)
	{
		// пропускаем элементы, находящиеся в той же
		// строке, но в столбцах с меньшим номером
		while(current != NULL && j > current->a.j)
		{
			current = current->next;
			prev = prev->next;
		}
		// если элемент с заданной позицией найден,
		// удаляем его
		if(current != NULL && j == current->a.j)
		{
			prev->next = current->next;
			delete current;
		}
	}
}
// метод получения элемента матрицы с заданными индексами
ListElement* MatrixList::ExistsElement(int i, int j)
{
	ListElement* exists = NULL;
	ListElement* current = head;
	// пропускаем элементы, находящиеся
	// до требуемого элемента
	while (current != NULL)
	{
		if (!(current->a.i < i || (current->a.i == i && current->a.j < j)))
			break;
		current = current->next;
	}
	// если элемент найден, запоминаем в exists его
	// адрес, в противном случае exists остается равным NULL
	if (current != NULL && current->a.i == i && current->a.j == j)
		exists = current;
	return exists;
}

// операция сложения двух матриц
MatrixList MatrixList::operator+(MatrixList& ob)
{
	if(m != ob.m || n != ob.n)
		throw "Матрицы должны иметь одинаковые размеры";
	// создается матрица-результат
	// как копия первого слагаемого
	MatrixList temp(*this);
	ListElement* current = ob.head;
	ListElement* exists;
	// просмотр элементов второй матрицы
	while (current != NULL)
	{
		exists = temp.ExistsElement(current->a.i,
			current->a.j);
		if (exists != NULL)
			// если в матрице-результате элемент
				// с такими индексами уже имеется,
					// суммируем элементы
						exists->a.value += current->a.value;
		else
			// если в матрице-результате элемент с
			// такими индексами не существует,
			// добавляем новый элемент
			// в матрицу-результат
			temp.AddElement(current-> a.i, current->a.j,
			current->a.value);
		current = current->next;
	}
	return temp;
}

// метод проверки, является ли матрицы трехдиагональной
bool MatrixList::IsTripleDiagonal()
{
	// если матрица неквадратная, генерируется исключение
	if(m != n) throw "Матрица неквадратная";
	ListElement* exists1;
	// в каждой строке проверяется наличие ненулевых
	// элементов, расположенных до трех центральных
	// диагоналей и после них. Если ненулевой элемент
	// будет найден, матрица не является
	// трехдиагональной.
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < i - 1; j++)
		{
			exists1 = ExistsElement(i, j);
			if(exists1 != NULL)
				return false;
		}
		for(int j = i + 2; j < n; j++)
		{
			exists1 = ExistsElement(i, j);
			if(exists1 != NULL)
				return false;
		}
	}
	return true;
}