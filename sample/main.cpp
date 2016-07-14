#include "MatrixList.h"

void main()
{
	try
	{
		MatrixList a(5,5);
		for (int i = 0, j = 4; i < 5; i++, j--) 
			a.AddElement(i,j,5);
		cout << "Matrix a = " << endl <<endl << a << endl;
		MatrixList b(5,5);
		for (int i = 0, j = 0; i < 5; i++, j++) 
			b.AddElement(i,j,5);
		cout << "Matrix  b = " << endl << endl << b << endl;
		cout << "Matrix c = a + b " << endl << endl << a + b << endl;
	}
	catch(const char* error)
	{
		cout << error << endl;
	}
}