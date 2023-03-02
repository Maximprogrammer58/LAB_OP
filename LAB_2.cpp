#define _CRT_SECURE_NO_WARNINGS
#define N 8

#include <stdio.h>
#include <locale.h>

// ��������� ����� �������� 8 �� 8
char chess_board[N][N];

// ���������� ������� ����� 
int x0, y0;

bool flag;

char visual_board[N][N];

int correctInput(char);

void addQueen(int, int);

void deleteQueen(int, int);

void solve_lab(int);

void startPrint(char);

void reset(void);

void visual_alg(int, int);

int main()
{
	while (true)
	{
		setlocale(LC_ALL, "");

		int output;

		flag = true;

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				chess_board[i][j] = 0;

		printf("� ����� ������ �� ��������� �����?\n");
		printf("������� x0 - ����� ������ � y0 - ����� ������� �����, ��� 1 <= x0 <= 8, 1 <= y0 <= 8  \n");

		x0 = correctInput('x');
		y0 = correctInput('y');

		addQueen(x0, y0);

		printf("��� ����� ������� ������� ����� ��������� ����� ���������� � ������ �������: \n");
		solve_lab(0);

		printf("������� ���������� ��������� ����� �� ������: \n");
		visual_alg(x0, y0);

		printf("������� �����-�������: 1 - ������ ��������� ���������, 0 - ������� �������:\n");
		while (true)
		{
			printf("������� �������: ");
			scanf_s("%d", &output);
			if ((output == 0) || (output == 1))
				break;
			printf("�� ����� ������������ �����-�������, ���������� �����\n");
		}

		if (output == 0) break;
	}

	return 0;
}

// �������� ������������ ����� ������
int correctInput(char name)
{
	int x;
	while (true)
	{
		printf("%c = ", name);
		scanf_s("%d", &x);
		if ((x >= 1) && (x <= 8))
			return x - 1;
		printf("������ �����, ���������� �����\n");
	}
}

// ������� ��� ����������� ����� � ��� ���� �� �������� ����������� 
void addQueen(int i, int j)
{
	for (int x = 0; x < 8; x++)
	{
		chess_board[x][j] += 1;
		chess_board[i][x] += 1;
		if ((i - j + x >= 0) && (i - j + x < 8))
			chess_board[i - j + x][x] += 1;
		if ((i + j - x >= 0) && (i + j - x < 8))
			chess_board[i + j - x][x] += 1;
	}

	chess_board[i][j] = -1;
}

// ������� ��� �������� ����� � ��� ���� �� �������� ����������� 
void deleteQueen(int i, int j)
{
	for (int x = 0; x < 8; x++)
	{
		chess_board[x][j] -= 1;
		chess_board[i][x] -= 1;
		if ((i - j + x >= 0) && (i - j + x < 8))
			chess_board[i - j + x][x] -= 1;
		if ((i + j - x >= 0) && (i + j - x < 8))
			chess_board[i + j - x][x] -= 1;
	}

	chess_board[i][j] = 0;
}

// ����������� ������� ��� ������� ������
void solve_lab(int i)
{
	if (i != x0)
	{
		for (int j = 0; j < N; j++)
		{
			if ((chess_board[i][j] == 0))
			{
				addQueen(i, j);
				if (i == 7)
				{
					startPrint(' ');
					reset();
					break;
				}
				else
					solve_lab(i + 1);
				deleteQueen(i, j);
			}
		}
	}

	else if (i == 7)
	{
		if (flag)
		{
			startPrint(' ');
			reset();
			flag = false;
		}
	}

	else solve_lab(i + 1);
}

// ��������� "��������" ����� ��������� ����� � �������������� �������
void startPrint(char visual)
{
	char line[34] = "---------------------------------";
	for (int i = 0; i < N; i++)
	{
		printf("%s", line);
		printf("\n");
		printf("|");
		for (int j = 0; j < N; j++)
		{
			if (chess_board[i][j] == -1)
				printf(" Q |");
			else if (chess_board[i][j] >= 1)
				printf(" %c |", visual);
			else
				printf("   |");
		}

		printf("\n");
	}

	printf("%s", line);
	printf("\n");
}

void reset()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			visual_board[i][j] = chess_board[i][j];
}

void visual_alg(int x, int y)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			chess_board[i][j] = 0;

	addQueen(x, y);
	startPrint('*');

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			if ((i != x) && (visual_board[i][j] == -1))
			{
				addQueen(i, j);
				startPrint('*');
			}
		}
}