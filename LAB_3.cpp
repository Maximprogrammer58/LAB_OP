#define _CRT_SECURE_NO_WARNINGS
#define N 1001
#define SIZE 34

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

char new_text[2 * N], lower_text[N];
int indexArray[N] = { 0 };
int count = 0, len = 0,
free_int = 0, text_len = 0;

void reset();
void Set_Newtext(char* str);
void add_Int_element(int index);
void add_brackets(int n, int index);
void Set_Lowertext(char* str, char* Upper_alf, char* Lower_alf);
void processing(char* str, char* delimeters, char first_letter, char last_letter);
char length(const char* str);
char tolowerCase(char* p_upper, char* p_lower, char element);
bool isDelimeter(char symbol, char* str);

int main()
{
	setlocale(LC_ALL, "");
	system("chcp 1251");
	system("cls");

	while (true)
	{
		char a, b;

		char text[N],
			Upper_alf[SIZE] = "јЅ¬√ƒ≈®∆«»… ЋћЌќѕ–—“”‘’÷„ЎўЏџ№Ёёя",
			Lower_alf[SIZE] = "абвгдеЄжзийклмнопрстуфхцчшщъыьэю€",
			delimeters[] = " .,;:!-?\"\'\n";

		reset();

		printf("¬ведите текст, не превышающий 1000 символов.\n");
		fgets(text, N, stdin);
		fflush(stdin);

		printf("¬ведите буквы, на которые начинаетс€ и заканчиватс€ слово.\n");
		a = getchar();
		getchar();
		b = getchar();
		getchar();

		Set_Lowertext(text, Upper_alf, Lower_alf);
		Set_Newtext(text);

		text_len = length(text);

		processing(lower_text, delimeters, tolowerCase(Upper_alf, Lower_alf, a), tolowerCase(Upper_alf, Lower_alf, b));

		for (int i = 0; i < len; i++)
			add_brackets(indexArray[i], i);

		printf("¬ведЄнный текст:\n");
		printf("%s\n", text);

		printf("ѕреобразованный текст:\n");
		printf("%s\n", new_text);

		printf(" оличество слов, имеющих маску %c*%c равно %d\n", a, b, count);

		int n;
		printf("¬ведите 0, чтобы завершить программу, иначе напечатайте другое любое число дл€ продолжени€ работы.\n");
		scanf_s("%d", &n);
		getchar();

		if (n == 0)
			break;
	}

	return 0;
}

char length(const char* str)
{
	const char* p = str;
	while (*p) p++;
	return p - str;
}

void Set_Lowertext(char* str, char* Upper_alf, char* Lower_alf)
{
	int j = 0;
	char* p = str;

	while (*p)
	{
		lower_text[j] = tolowerCase(Upper_alf, Lower_alf, *p);
		p++;
		j++;
	}
}

void Set_Newtext(char* str)
{
	int j = 0;
	char* p = str;

	while (*p)
	{
		new_text[j] = *p;
		p++;
		j++;
	}
}

bool isDelimeter(char symbol, char* str)
{
	while (*str)
	{
		if (symbol == *str)
			return true;
		str++;
	}

	return false;
}

char tolowerCase(char* p_upper, char* p_lower, char element)
{
	char symbol = element;
	for (int i = 0; i < SIZE - 1; i++)
		if (symbol == p_upper[i])
			symbol = p_lower[i];
	return symbol;
}

void processing(char* str, char* delimeters, char first_letter, char last_letter)
{
	int index = 0;

	while (*str)
	{
		if ((*str) && (isDelimeter(*str, delimeters)))
		{
			while ((*str) && (isDelimeter(*str, delimeters)))
			{
				str++;
				index++;
			}
		}

		else
		{
			bool flag_for_symbols = true,
				flag_for_count = true;

			int first_index = 0;

			if (*str == first_letter)
				first_index = index;

			else
				flag_for_symbols = false;

			while ((*str) && (!isDelimeter(*str, delimeters)))
			{
				if (((isDelimeter(*(str + 1), delimeters)) || (!(*(str + 1)))) && (*str == last_letter) && (flag_for_symbols))
				{
					add_Int_element(first_index);
					add_Int_element(index);
					count++;
				}

				str++;
				index++;
			}
		}
	}
}

void reset()
{
	count = 0;
	len = 0;
	free_int = 0;
	int indexArray[N] = { 0 };
}

void add_Int_element(int index)
{
	indexArray[free_int] = index;
	free_int++;
	len++;
}

void add_brackets(int n, int index)
{
	text_len++;
	int num = n;

	for (int i = 0; i < text_len; i++)
	{
		if (i == n)
		{
			if (index % 2 != 0)
			{
				new_text[text_len - 1] = ')';
				num++;
			}

			else
				new_text[text_len - 1] = '(';

			for (int k = text_len - 1; k > num; k--)
			{
				char temp = new_text[k];
				new_text[k] = new_text[k - 1];
				new_text[k - 1] = temp;
			}
		}
	}

	for (int i = 0; i < len; i++)
		indexArray[i]++;
}
