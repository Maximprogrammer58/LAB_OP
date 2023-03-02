#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#define SIZE 255
#define EPSILON 0.0000000001f

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

int count = 0, carriage = 0;
double populations;
char name[SIZE] = "", country[SIZE] = "", path[SIZE] = "";
bool isFree = true;

struct City
{
	char name[SIZE], country[SIZE];
	double populations;
};

double correct_populations();

int menu1();
int menu2();
int get_key();
int count_records();
int find_record(City*);
int strcmp_no_case(char*, char*);

void text_menu1();
void text_menu2();
void output(City*);
void next_record(City*);
void output_record(City*);
void output_to_file(City*);
void previous_record(City*);
void output_with_check(City*);

City* clear(City*);
City* input(City*, int, int);
City* add_record(City*, int);
City* editing(City*, int);
City* add_record_END(City*);
City* Bubble_sorting(City*);
City* remove_record(City*, int);

int main()
{
	setlocale(LC_ALL, "");
	system("chcp 1251");
	system("cls");
	system("color 0B");

	int index = 0, choice = 0, repeal = 0;

	City* city = (City*)malloc(sizeof(City));

	if (city == NULL)
	{
		printf("Ошибка при выделении памяти для данных\n");
		return 1;
	}

	text_menu1();

	while (true)
	{
		int m1 = menu1();

		if (m1 == 27)
		{
			printf("Введите 1, чтобы сохранить данные в файл или 2 для выхода без сохранения:\n");
			choice = getch();

			if (choice == 49)
			{
				output_to_file(city);
				break;
			}

			else if (choice == 50)
				break;
		}

		if (m1 == 51)
		{
			system("cls");
			text_menu2();
			output(city);

			while (true)
			{
				int m2 = menu2();

				if (m2 == 27)
				{
					system("cls");
					text_menu1();
					output(city);
					break;
				}

				switch (m2)
				{
					case 49:
						city = add_record_END(city);
						break;

					case 50:
						index = carriage;
						city = add_record(city, index + 1);
						break;

					case 56:
						index = find_record(city);
						city = add_record(city, index + 1);
						break;

					case 57:
						if (isFree)
							printf("Массив пуст\n");
						else
						{
							index = find_record(city);
							city = remove_record(city, index);
						}
						break;

					case 51:
						if (isFree)
							printf("Массив пуст\n");
						else
						{
							index = carriage;
							city = remove_record(city, index);
						}
						break;

					case 52:

						if (isFree)
							printf("Массив пуст\n");
						else
						{
							index = carriage;
							city = editing(city, index);
						}
						break;

					case 48:
						index = find_record(city);
						city = editing(city, index);
						break;

					case 53:
						system("cls");
						text_menu2();
						if (isFree)
							printf("Массив пуст\n");
						else
							output_record(city);
						break;

					case 54:
						system("cls");
						text_menu2();
						if (isFree)
							printf("Массив пуст\n");
						else
						{
							next_record(city);
							output_record(city);
						}
						break;

					case 55:
						system("cls");
						text_menu2();
						if (isFree)
							printf("Массив пуст\n");
						else
						{
							previous_record(city);
							output_record(city);
						}
						break;
				}
			}
		}

		switch (m1)
		{
			case 49:
				index = count;
				repeal = count_records();
				if (repeal == -1)
					printf("Ошибка при открытии файла, попробуйте снова нажать 1.\n");
				else
					city = input(city, index, repeal);
				break;

			case 52:
				output_to_file(city);
				break;

			case 50:
				free(city);
				city = clear(city);
				break;

			case 53:
				output_with_check(city);
				break;
		}
	}

	free(city);

	return 0;
}

int get_key()
{
	int key = getch();
	if ((key == 0) || (key == 224))
		key = getch();
	return key;
}

int menu1()
{
	while (true)
	{
		int key = get_key();
		if ((key == 27) || (key == 49) || (key == 50) || (key == 51) || (key == 52) || (key == 53))
			return key;
	}
}

void text_menu1()
{
	printf("__________________________________\n");
	printf("|               Меню             |\n");
	printf("----------------------------------\n");
	printf("| 1 - загрузить данные из файла  |\n");
	printf("| 2 - очистить массив данных     |\n");
	printf("| 3 - работа с данными           |\n");
	printf("| 4 - сохранить данные в файл    |\n");
	printf("| 5 - сохранить в файл результат |\n");
	printf("| Esc - выход                    |\n");
	printf("----------------------------------\n");
}

void text_menu2()
{
	printf("_______________________________________\n");
	printf("|          Работа с данными           |\n");
	printf("---------------------------------------\n");
	printf("| 1 - добавить запись                 |\n");
	printf("| 2 - добавить запись после текущей   |\n");
	printf("| 3 - удалить текущую запись          |\n");
	printf("| 4 - изменить текущую запись         |\n");
	printf("| 5 - текущая запись (помечена -->)   |\n");
	printf("| 6 - следующая запись                |\n");
	printf("| 7 - предыдущая запись               |\n");
	printf("| 8 - добавить запись после указанной |\n");
	printf("| 9 - удалить указанную запись        |\n");
	printf("| 0 - изменить указанную запись       |\n");
	printf("| Esc - назад                         |\n");
	printf("---------------------------------------\n");
}

int menu2()
{
	while (true)
	{
		int key = get_key();
		if ((key == 27) || (key == 48) || (key == 49) || (key == 50) || (key == 51) || (key == 52) || (key == 53) || (key == 54) || (key == 55) || (key == 56) || (key == 57))
			return key;
	}
}

int count_records()
{
	int repeal = 0;

	FILE* fp = NULL;

	printf("Введите путь к файлу или его название c расширением \'.txt\': ");
	fgets(path, SIZE, stdin);
	fflush(stdin);

	path[strlen(path) - 1] = '\0';

	fp = fopen(path, "r");

	if (!fp)
		return -1;

	char* str = (char*)malloc(SIZE * sizeof(char));

	while (fgets(str, SIZE, fp))
	{
		count++;
		repeal++;
	}

	free(str);

	fclose(fp);

	return repeal;
}

City* input(City* city, int index, int repeal)
{
	bool start_output = true;

	FILE* fp = fopen(path, "r");

	city = (City*)realloc(city, count * sizeof(City));

	while (!feof(fp))
	{
		if (fscanf(fp, "%s\t%s\t%lf\n", name, country, &populations) != 3)
		{
			printf("Данные в файле некорректны\n");
			start_output = false;
		}

		else
		{
			if (populations > EPSILON)
			{
				strcpy(city[index].name, name);
				strcpy(city[index].country, country);
				city[index].populations = populations;
				index++;
			}

			else
			{
				start_output = false;
				printf("Проверьте корректность введенного населения и попробуйте снова\n");
			}
		}
	}

	isFree = false;

	fclose(fp);

	if (start_output)
	{
		system("cls");
		text_menu1();
		output(city);
	}

	else
	{
		count -= repeal;
		city = (City*)realloc(city, count * sizeof(City));
		printf("Попробуйте снова\n");
	}

	return city;
}

void output(City* city)
{
	if ((isFree) || (count == 0))
		printf("Массив пустой\n");

	else
	{
		printf("______________________________________________________\n");
		printf("|     Город  \t|    Страна   \t| Население (млн чел) |\n");
		printf("------------------------------------------------------\n");
		for (int i = 0; i < count; i++)
			fprintf(stdout, "| %10s   \t| %10s  \t|      %9.4lf      |\n", city[i].name, city[i].country, city[i].populations);
		printf("------------------------------------------------------\n");
	}
}

void output_to_file(City* city)
{
	char file[SIZE] = "";

	FILE* fp = NULL;

	while (true)
	{
		printf("Введите путь к файлу или его название c расширением \'.txt\': ");
		fgets(file, SIZE, stdin);
		fflush(stdin);

		file[strlen(file) - 1] = '\0';

		fp = fopen(file, "w");

		if (!fp)
			printf("Error\n");
		else
			break;
	}

	for (int i = 0; i < count; i++)
		fprintf(fp, "%s \t%s\t%.2lf\n", city[i].name, city[i].country, city[i].populations);

	system("cls");
	text_menu1();
	printf("Данные сохранены в файл\n");

	fclose(fp);
}

void output_with_check(City* city)
{
	double people;
	char file[SIZE] = "";

	FILE* fp = NULL;

	while (true)
	{
		printf("Введите путь к файлу или его название c расширением \'.txt\': ");
		fgets(file, SIZE, stdin);
		fflush(stdin);

		file[strlen(file) - 1] = '\0';

		fp = fopen(file, "w");

		if (!fp)
			printf("Error\n");
		else
			break;
	}

	printf("Введите страну:");
	fgets(country, SIZE, stdin);
	fflush(stdin);
	country[strlen(country) - 1] = '\0';
	printf("Введите население в млн: ");
	people = correct_populations();

	city = Bubble_sorting(city);

	for (int i = 0; i < count; i++)
	{
		if ((city[i].populations > people) && (strcmp_no_case(city[i].country, country) == 0))
			fprintf(fp, "%s \t%s\t%.2lf\n", city[i].name, city[i].country, city[i].populations);
	}

	system("cls");
	text_menu1();
	printf("Данные сохранены в файл\n");

	fclose(fp);
}

City* add_record_END(City* city)
{
	printf("Введите новую запись: город, страну, население\n");
	printf("Введите город:");
	fgets(name, SIZE, stdin);
	fflush(stdin);
	printf("Введите страну:");
	fgets(country, SIZE, stdin);
	fflush(stdin);
	printf("Введите население в млн.человек:");
	populations = correct_populations();

	name[strlen(name) - 1] = '\0';
	country[strlen(country) - 1] = '\0';

	count++;
	city = (City*)realloc(city, count * sizeof(City));
	strcpy(city[count - 1].name, name);
	strcpy(city[count - 1].country, country);
	city[count - 1].populations = populations;

	isFree = false;

	system("cls");
	text_menu2();
	output(city);

	return city;
}

City* remove_record(City* city, int index)
{
	if ((index == -1) || (count == 0))
	{
		system("cls");
		text_menu2();
		if (index == -1)
		{
			printf("Такого города нет\n");
			output(city);
		}
		else
			printf("Массив пуст\n");
	}

	else
	{
		for (int i = 0; i < count - 1; i++)
			if (i >= index)
				city[i] = city[i + 1];
		count--;

		city = (City*)realloc(city, count * sizeof(City));

		system("cls");
		text_menu2();
		if (count + 1 == 1)
			printf("Массив пуст\n");
		else
			output(city);
	}

	return city;
}

City* editing(City* city, int index)
{
	if (index == -1)
	{
		system("cls");
		text_menu2();
		printf("Такого города нет\n");
	}

	else
	{
		printf("Что будем редактировать?\n");
		printf("1 - город\n");
		printf("2 - страну\n");
		printf("3 - население\n");
		printf("4 - город и страну\n");
		printf("5 - город и население\n");
		printf("6 - страну и население\n");
		printf("7 - город, страну и население\n");

		int choice = get_key();

		switch (choice)
		{
			case 49:
				printf("Введите город:");
				fgets(name, SIZE, stdin);
				fflush(stdin);
				name[strlen(name) - 1] = '\0';
				strcpy(city[index].name, name);
				break;

			case 50:
				printf("Введите страну:");
				fgets(country, SIZE, stdin);
				fflush(stdin);
				country[strlen(country) - 1] = '\0';
				strcpy(city[index].country, country);
				break;

			case 51:
				printf("Введите население в млн.человек:");
				populations = correct_populations();
				city[index].populations = populations;
				break;

			case 52:
				printf("Введите город:");
				fgets(name, SIZE, stdin);
				fflush(stdin);
				printf("Введите страну:");
				fgets(country, SIZE, stdin);
				fflush(stdin);
				name[strlen(name) - 1] = '\0';
				country[strlen(country) - 1] = '\0';
				strcpy(city[index].name, name);
				strcpy(city[index].country, country);
				break;

			case 53:
				printf("Введите город:");
				fgets(name, SIZE, stdin);
				fflush(stdin);
				printf("Введите население в млн.человек:");
				populations = correct_populations();
				name[strlen(name) - 1] = '\0';
				strcpy(city[index].name, name);
				city[index].populations = populations;
				break;

			case 54:
				printf("Введите страну:");
				fgets(country, SIZE, stdin);
				fflush(stdin);
				printf("Введите население в млн.человек:");
				populations = correct_populations();
				country[strlen(country) - 1] = '\0';
				strcpy(city[index].country, country);
				city[index].populations = populations;
				break;

			case 55:
				printf("Введите город:");
				fgets(name, SIZE, stdin);
				fflush(stdin);
				printf("Введите страну:");
				fgets(country, SIZE, stdin);
				fflush(stdin);
				printf("Введите население в млн.человек:");
				populations = correct_populations();
				name[strlen(name) - 1] = '\0';
				country[strlen(country) - 1] = '\0';
				strcpy(city[index].name, name);
				strcpy(city[index].country, country);
				city[index].populations = populations;
				break;
		}

		system("cls");
		text_menu2();
	}

	output(city);

	return city;
}

City* Bubble_sorting(City* city)
{
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count - i - 1; j++)
		{
			if (strcmp_no_case(city[j].name, city[j + 1].name) > 0)
			{
				City tmp = city[j];
				city[j] = city[j + 1];
				city[j + 1] = tmp;
			}
		}
	}

	return city;
}

City* add_record(City* city, int index)
{
	if (index == 0)
	{
		system("cls");
		text_menu2();
		printf("Такого города нет\n");
	}

	else
	{
		printf("Введите новую запись: город, страну, население\n");
		printf("Введите город:");
		fgets(name, SIZE, stdin);
		fflush(stdin);
		printf("Введите страну:");
		fgets(country, SIZE, stdin);
		fflush(stdin);
		printf("Введите население в млн.человек:");
		populations = correct_populations();

		name[strlen(name) - 1] = '\0';
		country[strlen(country) - 1] = '\0';

		count++;
		city = (City*)realloc(city, count * sizeof(City));
		strcpy(city[count - 1].name, name);
		strcpy(city[count - 1].country, country);
		city[count - 1].populations = populations;

		isFree = false;

		int j = count - 1;
		while (j != index)
		{
			for (int i = index; i < count - 1; i++)
			{
				City tmp = city[i];
				city[i] = city[i + 1];
				city[i + 1] = tmp;
			}

			j--;
		}

		system("cls");
		text_menu2();
	}

	output(city);

	return city;
}

void next_record(City* city)
{
	if (carriage != count - 1)
		carriage++;
}

void previous_record(City* city)
{
	if (carriage != 0)
		carriage--;
}

double correct_populations()
{
	double populations;

	while (true)
	{
		scanf_s("%lf", &populations);
		getchar();
		if (populations > EPSILON)
			return populations;
		else
			printf("Введите корректное значение\n");
	}
}

int strcmp_no_case(char* str1, char* str2)
{
	char str1_lower[SIZE] = "", str2_lower[SIZE] = "";

	for (int i = 0; i < strlen(str1); i++)
		str1_lower[i] = tolower(str1[i]);

	for (int i = 0; i < strlen(str2); i++)
		str2_lower[i] = tolower(str2[i]);

	return strcmp(str1_lower, str2_lower);
}

City* clear(City* city)
{
	system("cls");
	text_menu1();
	count = 0;
	isFree = true;

	printf("Массив очищен\n");
	city = (City*)malloc(sizeof(City));

	return city;
}

void output_record(City* city)
{
	if (isFree)
		printf("Массив пустой\n");

	else
	{
		printf("_______________________________________________________________\n");
		printf("|      Город     \t|    Страна   \t| Население (млн чел) |\n");
		printf("---------------------------------------------------------------\n");
		for (int i = 0; i < count; i++)
		{
			if (i == carriage)
				fprintf(stdout, "| --> %10s   \t| %10s  \t|      %9.4lf      |\n", city[i].name, city[i].country, city[i].populations);
			else
				fprintf(stdout, "|     %10s   \t| %10s  \t|      %9.4lf      |\n", city[i].name, city[i].country, city[i].populations);
		}
		printf("---------------------------------------------------------------\n");
	}
}

int find_record(City* city)
{
	printf("Введите город для поиска: ");
	fgets(name, SIZE, stdin);
	fflush(stdin);
	name[strlen(name) - 1] = '\0';

	for (int i = 0; i < count; i++)
		if (strcmp_no_case(city[i].name, name) == 0)
			return i;

	return -1;
}