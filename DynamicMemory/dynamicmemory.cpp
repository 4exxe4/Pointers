﻿#include <iostream>
using namespace std;
#define tab "\t"

template<typename T> T** Allocate(const int rows, const int cols);
template<typename T> void Clear(T**& arr, const int rows, const int cols = 0);

void FillRand(int arr[], const int n, int minRand = 0, int maxRand = 100);
void FillRand(double arr[], const int n, int minRand = 0, int maxRand = 100);
void FillRand(int** arr, const int rows, const int cols, int minRand = 0, int maxRand = 100);
template<typename T> void Print(T arr[], const int n);
template<typename T> void Print(T** arr, const int rows, const int cols);

template<typename T> T* push_back(T arr[], int& n, const T value);
template<typename T> T* push_front(T arr[], int& n, const T value);

template <typename T>T* insert(T arr[], int& n, const T value, const int index);

template <typename T>T* pop_back(T arr[], int& n);
template <typename T>T* pop_front(T arr[], int& n);

template <typename T> T** push_row_back(T** arr, int& rows, const int cols );
template <typename T> T** insert_row(T** arr, int& rows, const int cols, const int index);

template <typename T> void push_col_back(T** arr, const int rows, int& cols);


//#define DYNAMIC_MEMORY_1 - //Cntrl+Shift+U - смена регистра
#define DYNAMIC_MEMORY_2

#define DATATYPE double
typedef int DataType;

void main()
{
	setlocale(LC_ALL, "");

#ifdef DYNAMIC_MEMORY_1
	int n;
	cout << "Введите размер массива: "; cin >> n;
	DataType* arr = new DataType[n]; //Объявление динамического массива

	FillRand(arr, n);
	Print(arr, n);

	DataType value;
	cout << "Введите добавляемое значение: "; cin >> value;
	arr = push_back(arr, n, value);
	Print(arr, n);

	cout << "Введите добавляемое значение: "; cin >> value;
	arr = push_front(arr, n, value);
	Print(arr, n);

	int index;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	arr = insert(arr, n, value, index);
	Print(arr, n);

	arr = pop_back(arr, n);
	Print(arr, n);
	
	arr = pop_front(arr, n);
	Print(arr, n);

	//delete[] arr;

#endif DYNAMIC_MEMORY_1

/*
Двумерные динамические маасивы:

Для того, чтобы объявить двумерный динамический массив нужно объявить указатель на указатель и выделить память для массива указателей, который будет хранить адреса строк двумерного массива
и только после этого нужно выделять память под строки. 

Все это делается следующим образом:
*/
#ifdef DYNAMIC_MEMORY_2
	int rows;
	int cols;

	cout << "Введите количество строк: "; cin >> rows;
	cout << "Введите количество элементов строки: "; cin >> cols;

	int** arr = Allocate<int>(rows, cols);
	
	//Copy - функция НЕ изменяет переданную в нее память, а возвращает измененную копию полученной памяти.
	//Mutable - функция и
	FillRand(arr, rows, cols);
	Print(arr, rows, cols);

	arr = push_row_back(arr, rows, cols);
	FillRand(arr[rows - 1], cols, 100, 1000);
	Print(arr, rows, cols);
	
	push_col_back(arr, rows, cols);
	for (int i = 0; i < rows; i++)
	{
		arr[i][cols - 1] = rand() % 1000;
	}
	Print(arr, rows, cols);

	int index;
	cout << "Введите индекс добавляемого значения: "; cin >> index;
	arr = insert_row(arr, rows, cols, index);
	Print(arr, rows, cols);

	Clear(arr, rows, cols);

#endif DYNAMIC_MEMORY_2
/*
Обращаться к элементам двумерного динамического массива можно точно так же, как и к элементам двумерного статического массива, через арифметику указателей и оператор разыменования
или через оператор индексирования.

Для того, чтобы передать двумерный динамический массив в функцию, достаточно, чтобы функция принимала указатель на указатель и размер массива.
*/
}
template<typename T> T** Allocate(const int rows, const int cols)
{
	//1) Создаем массив указателей:

	T** arr = new T* [rows];

	//2) Выделяем память под строки:
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new T[cols];
	}
	return arr;
}
template<typename T> void Clear(T**& arr, const int rows, const int cols)
{
	//При удалении двумерного массива сначала удалются строки, как правило это происходит в цикле, и только после этого удаляется массив указателей

	//1) Сначала удаляются строки двумерного массива:
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}

	//2) Только теперь можно удалить массив указателей:
	delete[] arr;

	//3) Зануляем указатель на массив:
	arr = nullptr;
}

void FillRand(int arr[], const int n, int minRand, int maxRand)
{
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand() % (maxRand - minRand) + minRand; //Через арифметику указателей и оператор разыменовывания
	}
}
void FillRand(double arr[], const int n, int minRand, int maxRand)
{
	minRand *= 100;
	maxRand *= 100;
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand() % (maxRand - minRand) + minRand; //Через арифметику указателей и оператор разыменовывания
		arr[i] /= 100;
	}
}
void FillRand(int** arr, const int rows, const int cols, int minRand, int maxRand)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand() % (maxRand-minRand) + minRand;
		}
	}
}
void FillRand(double** arr, const int rows, const int cols, int minRand, int maxRand)
{
	minRand *= 100;
	maxRand *= 100;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = double (rand() % (maxRand - minRand) + minRand)/100;
		}
	}
}

template<typename T> void Print(T arr[], const int n)
{
	cout << arr << endl;
	cout << *arr << endl;
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << "\t"; //Через оператор индексирования
	}
	cout << endl;
}
template<typename T> void Print(T** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << arr[i][j] << tab;
		}
		cout << endl;
	}
	cout << endl;
}

template<typename T> T* push_back(T arr[], int& n, const T value)
{
	//1) Создаем буферный массив нужного размера:

	T* buffer = new T[n + 1];

	//2) Копируем все элементы из исходного массива в буферный:

	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];
	}

	//3) Удаляем исходный массив:

	delete[] arr;

	//4) Подменяем адрес исходного массива адресом нового массива:

	arr = buffer;
	buffer = nullptr; //nullptr - это указатель на ноль

	//5) Только после всего выше написанного, в массиве "arr" появляется элемент, в который можно сохранить добавляемое значение:

	arr[n] = value;

	//6) После добавления элемента в массив, количество его элементов увеличивается на 1

	n++;

	//7) Mission complete - значение добавлено
	return arr;
}
template<typename T> T* push_front(T arr[], int& n, const T value)
{
	//1) Создаем буферный массив

	T* buffer = new T[n + 1];
	
	//2)

	for (int i = 0; i < n; i++)
	{
		buffer[i + 1] = arr[i];
	}
	//3)

	delete[] arr;

	//4)

	buffer[0] = value;

	//5)

	n++;

	return buffer;
}

template <typename T> T* insert(T arr[], int& n, const T value, const int index)
{
	T* buffer = new T[n + 1]{};
	for (int i = 0; i < n; i++)buffer[i < index ? i : i + 1] = arr[i];
	delete[] arr;
	buffer[index] = value;
	n++;
	return buffer;
}

template <typename T> T* pop_back(T arr[], int& n)
{
	T* buffer = new T[--n];
	for (int i = 0; i < n; i++)buffer[i] = arr[i];
	delete[] arr;
	return buffer;
}
template <typename T> T* pop_front(T arr[], int& n)
{
	T* buffer = new T[--n];
	for (int i = 0; i < n; i++)buffer[i] = arr[i + 1];
	delete[]arr;
	return buffer;
}

template <typename T> T** push_row_back(T** arr, int& rows, const int cols)
{
	//1) Создаем буферный массив указателей:
	T** buffer = new T* [rows+1];

	//2) Копируем адреса строк в новый массив:
	for (int i = 0; i < rows; i++)
	{
		buffer[i] = arr[i];
	}
	
	//3) Удаляем исходный массив указателей
	delete[] arr;

	//4) Добавляем добавляемую строку:

	buffer[rows] = new T[cols] {};

	//5) После добавления строки, количество строк увеличивается на 1:

	rows++;

	//6) Возвращаем новый массив:
	return buffer;
}
template <typename T> T** insert_row(T** arr, int& rows, const int cols, const int index)
{
	if (index<0 || index>rows)
	{
		cout << "Error: Out of range exeption" << endl;
		return arr;
	}
	T** buffer = new T* [rows + 1] {};
	//for (int i = 0; i < index; i++)buffer[i] = arr[i];
	//for (int i = index; i < rows; i++)buffer[i + 1] = arr[i];
	for (int i = 0; i < rows; i++)
	{
		if (i < index)buffer[i] = arr[i];
		else buffer[i + 1] = arr[i];
	}
	delete[] arr;
	buffer[index] = new T [cols] {};
	rows++;
	return buffer;
}

template <typename T> void push_col_back(T** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		//1) Создаем буфферную строку нужного размера:
		T* buffer = new T[cols + 1] {};

		//2) Копируем элементы из исходной строки в буферную:

		for (int j = 0; j < cols; j++)
		{
			buffer[j] = arr[i][j];
		}
		//3) Удаляем исходную строку:

		delete[] arr[i];

		//4) Подменяем адрес исходной строки адресом новой строки:
		arr[i] = buffer;
	}
	cols++;
}

/*
Динамические массивы:

Для того, чтобы объявить динамический массив нужно объявить указатель и выделить память при помощи оператора "new".
Оператор "new" выделяет непрерывный блок памяти для n-элементов заданного типа (в нашем случае int) и возвращает адрес выделенной памяти. Этот адрес мы и записываем в указатель "arr".

Stack - это модель памяти из которой последний записанный элемент считывается первым (статическая память)
Heap - динамическая память.

Динамическую память распределяет операционная система, и оператор "new" как раз запрашивает эту память у операционной системы.

Передача динамического массива в функцию:

При передаче как статического, так и динамического массива в функцию, в неё копируется указатель на начальный элемент массива и функция, фактически, не знает, какой массив в неё передали.
Исходя из этого одна и та же функция может работать как со статическими, так и с динамическими массивами

При передаче массива в функцию в неё копируется адрес нулевого элемента массива, а следовательно и всего массива, потому что массив - это указатель

Удаление динамического массива:

Оператор "new" запрашивает выделяемую память у операционной системы и если у нее есть непрерывный блок памяти нужного размера - она выделяет её, 
а оператор "new" возвращает адрес выделенной памяти. В противном случае, если блока памяти нет, то оператор "new" бросает "исключение".

Если память выделилась и мы можем ее использовать, то после её использования её обязательно нужно вернуть обратно операционной системе. 
Потому что оператор "new" якобы берет эту память "в долг" у операционной системы. Эту задачу выполняет оператор "delete". 

Если память не возвращать, то возникает утечка памяти (memory leak). Если утечки памяти возникают постоянно, то рано или поздно вся свободная память в операционной системе закончится.
И это приведет к аварийному завершению нашей программы с потерей данных.

Оператор "delete" должен быть вызван столько раз, сколько был вызван оператор "new".
Оператор "delete" можно вызывать в разных функциях.
*/