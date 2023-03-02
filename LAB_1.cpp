#define _CRT_SECURE_NO_WARNINGS
#define N 100
#define M 150

#include <stdio.h>
#include <locale.h>

int input_size(char);

int main()
{
	setlocale(LC_ALL, "");

	int mas[N][M];

	// Объявление вектора результатов B(n)
	int B[N] = { 0 };

	int n = 0,
		m = 0;

	printf("Введите размерность массива, где n - количество строк, а m - количество столбцов\n");

	printf("Введите количество строк матрицы не больше 100\n");
	n = input_size('n');

	printf("Введите количество столбцов матрицы не больше 150\n");
	m = input_size('m');

	// Заполнение матрицы
	printf("Введите отдельно каждый элемент матрицы размером %d x %d\n", n, m);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			printf("A[%d][%d] = ", i, j);
			scanf_s("%d", &mas[i][j]);
		}

	// Вывод матрицы для проверки корректности её ввода
	printf("Вы ввели данную матрицу:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%4d", mas[i][j]);
		}
		printf("\n");
	}

	// Обработка матрицы
	for (int i = 0; i < n; i++)
	{
		// Присваиваем минимуму и максимуму значения первого элемента строки при каждой новой итерации цикла for по параметру i
		int min = mas[i][0],
			max = mas[i][0];

		for (int j = 0; j < m; j++)
		{
			if (mas[i][j] < min)
				min = mas[i][j];

			if (mas[i][j] > max)
				max = mas[i][j];
		}

		B[i] = min + max;
	}

	// Вывод вектора результатов B(n) с использованием тернарного оператора для визуализации ответа
	printf("Вывод вектора результатов: \n");
	printf("B(%d) = (", n);
	for (int k = 0; k < n; k++)
		(k != (n - 1)) ? printf("%d, ", B[k]) : printf("%d", B[k]);
	printf(")");

	return 0;
}

int input_size(char name)
{
	int x;
	while (true)
	{
		printf("%c = ", name);
		scanf_s("%d", &x);
		if ((x > 0) && (x <= 100))
			return x;
		printf("Ошибка ввода, попробуйте снова\n");
	}
}