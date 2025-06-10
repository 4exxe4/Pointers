#include <iostream>
using namespace std;

void FillRand(int arr[], const int n);
void Print(int arr[], const int n);

void main()
{
	setlocale(LC_ALL, "");
	const int n = 10;
	int arr[n];
	FillRand(arr, n);
	Print(arr, n);

	//1) Подсчет количества четных и нечетных элементов:

	int even_count = 0; //Количество четных элементов
	int odd_count = 0; //Количество нечетных элементов

	for (int i = 0; i < n; i++)
	{
		if (arr[i] % 2 == 0)even_count++;
		else odd_count++;
	}
	cout << "Количество четных элементов: " << even_count << endl;
	cout << "Количество нечетных элементов: " << odd_count << endl;

	//2) Выделяем память под массивы:

	int* even_arr = new int[even_count];
	int* odd_arr = new int[odd_count];

	//3) Копируем четные и нечетные элементы в соответствующие массивы:
	for (int i = 0, j = 0, k = 0; i < n; i++)
	{
		if (arr[i] % 2 == 0)even_arr[j++] = arr[i];
		else odd_arr[k++] = arr[i];
	}

	//4) Выводим массивы на экран:
	Print(even_arr, even_count);
	Print(odd_arr, odd_count);

	//?) Удаляем динамические массивы:

	delete[] odd_arr;
	delete[] even_arr;
}

void FillRand(int arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 100;
	}
}
void Print(int arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
}