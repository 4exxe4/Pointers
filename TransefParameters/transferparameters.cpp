#include <iostream>
using namespace std;

void Exchange(int a, int b);

void main()
{
	setlocale(LC_ALL, "");
	int a = 2, b = 3;
	cout << a << "\t" << b << endl;
	Exchange(a, b);
	cout << a << "\t" << b << endl;
}

void Exchange(int a, int b)
{
	int buffer = a;
	a = b;
	b = buffer;
}
/*
Передача параметров в функцию:

Существует 3 способа передать параметры в функцию:
1) По значению (by value)
2) По указателю (by pointer)
3) По ссылке (by reference)

Все время до этого мы передавали параметры в функцию по значению, при этом значения передаваемых переменных копируются в функцию.
Если функция изменяет переданные в неё значения, то изменения происходят с их копиями, а оригиналы остаются неизменными
*/