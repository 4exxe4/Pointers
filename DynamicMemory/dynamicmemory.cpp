#include <iostream>
using namespace std;
#define tab "\t"

int** Allocate(const int rows, const int cols);
void Clear(int**& arr, const int rows, const int cols = 0);

void FillRand(int arr[], const int n, int minRand = 0, int maxRand = 100);
void FillRand(int** arr, const int rows, const int cols, int minRand = 0, int maxRand = 100);
void Print(int arr[], const int n);
void Print(int** arr, const int rows, const int cols);

int* push_back(int arr[], int& n, const int value);
int* push_front(int arr[], int& n, const int value);

int* pop_back(int arr[], int& n);
int* pop_front(int arr[], int& n);

int** push_row_back(int** arr, int& rows, const int cols );
void push_col_back(int** arr, const int rows, int& cols);

int** insert_row(int** arr, int& rows, const int cols, const int index);


//#define DYNAMIC_MEMORY_1 - //Cntrl+Shift+U - ����� ��������
#define DYNAMIC_MEMORY_2

void main()
{
	setlocale(LC_ALL, "");

#ifdef DYNAMIC_MEMORY_1
	int n;
	cout << "������� ������ �������: "; cin >> n;
	int* arr = new int[n]; //���������� ������������� �������

	FillRand(arr, n);
	Print(arr, n);

	int value;
	cout << "������� ����������� ��������: "; cin >> value;
	arr = push_back(arr, n, value);
	Print(arr, n);

	cout << "������� ����������� ��������: "; cin >> value;
	arr = push_front(arr, n, value);
	Print(arr, n);

	arr = pop_back(arr, n);
	Print(arr, n);
	
	arr = pop_front(arr, n);
	Print(arr, n);

	//delete[] arr;

#endif DYNAMIC_MEMORY_1

/*
��������� ������������ �������:

��� ����, ����� �������� ��������� ������������ ������ ����� �������� ��������� �� ��������� � �������� ������ ��� ������� ����������, ������� ����� ������� ������ ����� ���������� �������
� ������ ����� ����� ����� �������� ������ ��� ������. 

��� ��� �������� ��������� �������:
*/

	int rows;
	int cols;

	cout << "������� ���������� �����: "; cin >> rows;
	cout << "������� ���������� ��������� ������: "; cin >> cols;

	int** arr = Allocate(rows, cols);
	
	//Copy - ������� �� �������� ���������� � ��� ������, � ���������� ���������� ����� ���������� ������.
	//Mutable - ������� �
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
	cout << "������� ������ ������������ ��������: "; cin >> index;
	arr = insert_row(arr, rows, cols, index);
	Print(arr, rows, cols);

	Clear(arr, rows, cols);

/*
���������� � ��������� ���������� ������������� ������� ����� ����� ��� ��, ��� � � ��������� ���������� ������������ �������, ����� ���������� ���������� � �������� �������������
��� ����� �������� ��������������.

��� ����, ����� �������� ��������� ������������ ������ � �������, ����������, ����� ������� ��������� ��������� �� ��������� � ������ �������.
*/
}
int** Allocate(const int rows, const int cols)
{
	//1) ������� ������ ����������:

	int** arr = new int* [rows];

	//2) �������� ������ ��� ������:
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new int[cols];
	}
	return arr;
}
void Clear(int**& arr, const int rows, const int cols)
{
	//��� �������� ���������� ������� ������� �������� ������, ��� ������� ��� ���������� � �����, � ������ ����� ����� ��������� ������ ����������

	//1) ������� ��������� ������ ���������� �������:
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}

	//2) ������ ������ ����� ������� ������ ����������:
	delete[] arr;

	//3) �������� ��������� �� ������:
	arr = nullptr;
}

void FillRand(int arr[], const int n, int minRand, int maxRand)
{
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand() % (maxRand - minRand) + minRand; //����� ���������� ���������� � �������� ���������������
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

void Print(int arr[], const int n)
{
	cout << arr << endl;
	cout << *arr << endl;
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << "\t"; //����� �������� ��������������
	}
	cout << endl;
}
void Print(int** arr, const int rows, const int cols)
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

int* push_back(int arr[], int& n, const int value)
{
	//1) ������� �������� ������ ������� �������:

	int* buffer = new int[n + 1];

	//2) �������� ��� �������� �� ��������� ������� � ��������:

	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];
	}

	//3) ������� �������� ������:

	delete[] arr;

	//4) ��������� ����� ��������� ������� ������� ������ �������:

	arr = buffer;
	buffer = nullptr; //nullptr - ��� ��������� �� ����

	//5) ������ ����� ����� ���� �����������, � ������� "arr" ���������� �������, � ������� ����� ��������� ����������� ��������:

	arr[n] = value;

	//6) ����� ���������� �������� � ������, ���������� ��� ��������� ������������� �� 1

	n++;

	//7) Mission complete - �������� ���������
	return arr;
}
int* push_front(int arr[], int& n, const int value)
{
	//1) ������� �������� ������

	int* buffer = new int[n + 1];
	
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

int* pop_back(int arr[], int& n)
{
	int* buffer = new int[--n];
	for (int i = 0; i < n; i++)buffer[i] = arr[i];
	delete[] arr;
	return buffer;
}
int* pop_front(int arr[], int& n)
{
	int* buffer = new int[--n];
	for (int i = 0; i < n; i++)buffer[i] = arr[i + 1];
	delete[]arr;
	return buffer;
}

int** push_row_back(int** arr, int& rows, const int cols)
{
	//1) ������� �������� ������ ����������:
	int** buffer = new int* [rows+1];

	//2) �������� ������ ����� � ����� ������:
	for (int i = 0; i < rows; i++)
	{
		buffer[i] = arr[i];
	}
	
	//3) ������� �������� ������ ����������
	delete[] arr;

	//4) ��������� ����������� ������:

	buffer[rows] = new int[cols] {};

	//5) ����� ���������� ������, ���������� ����� ������������� �� 1:

	rows++;

	//6) ���������� ����� ������:
	return buffer;
}
void push_col_back(int** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		//1) ������� ��������� ������ ������� �������:
		int* buffer = new int[cols + 1] {};

		//2) �������� �������� �� �������� ������ � ��������:

		for (int j = 0; j < cols; j++)
		{
			buffer[j] = arr[i][j];
		}
		//3) ������� �������� ������:

		delete[] arr[i];

		//4) ��������� ����� �������� ������ ������� ����� ������:
		arr[i] = buffer;
	}
	cols++;
}

int** insert_row(int** arr, int& rows, const int cols, const int index)
{
	if (index<0 || index>rows)
	{
		cout << "Error: Out of range exeption" << endl;
		return arr;
	}
	int** buffer = new int* [rows + 1] {};
	//for (int i = 0; i < index; i++)buffer[i] = arr[i];
	//for (int i = index; i < rows; i++)buffer[i + 1] = arr[i];
	for (int i = 0; i < rows; i++)
	{
		if (i < index)buffer[i] = arr[i];
		else buffer[i + 1] = arr[i];
	}
	delete[] arr;
	buffer[index] = new int [cols] {};
	rows++;
	return buffer;
}
/*
������������ �������:

��� ����, ����� �������� ������������ ������ ����� �������� ��������� � �������� ������ ��� ������ ��������� "new".
�������� "new" �������� ����������� ���� ������ ��� n-��������� ��������� ���� (� ����� ������ int) � ���������� ����� ���������� ������. ���� ����� �� � ���������� � ��������� "arr".

Stack - ��� ������ ������ �� ������� ��������� ���������� ������� ����������� ������ (����������� ������)
Heap - ������������ ������.

������������ ������ ������������ ������������ �������, � �������� "new" ��� ��� ����������� ��� ������ � ������������ �������.

�������� ������������� ������� � �������:

��� �������� ��� ������������, ��� � ������������� ������� � �������, � �� ���������� ��������� �� ��������� ������� ������� � �������, ����������, �� �����, ����� ������ � �� ��������.
������ �� ����� ���� � �� �� ������� ����� �������� ��� �� ������������, ��� � � ������������� ���������

��� �������� ������� � ������� � �� ���������� ����� �������� �������� �������, � ������������� � ����� �������, ������ ��� ������ - ��� ���������

�������� ������������� �������:

�������� "new" ����������� ���������� ������ � ������������ ������� � ���� � ��� ���� ����������� ���� ������ ������� ������� - ��� �������� �, 
� �������� "new" ���������� ����� ���������� ������. � ��������� ������, ���� ����� ������ ���, �� �������� "new" ������� "����������".

���� ������ ���������� � �� ����� �� ������������, �� ����� � ������������� � ����������� ����� ������� ������� ������������ �������. 
������ ��� �������� "new" ����� ����� ��� ������ "� ����" � ������������ �������. ��� ������ ��������� �������� "delete". 

���� ������ �� ����������, �� ��������� ������ ������ (memory leak). ���� ������ ������ ��������� ���������, �� ���� ��� ������ ��� ��������� ������ � ������������ ������� ����������.
� ��� �������� � ���������� ���������� ����� ��������� � ������� ������.

�������� "delete" ������ ���� ������ ������� ���, ������� ��� ������ �������� "new".
�������� "delete" ����� �������� � ������ ��������.
*/