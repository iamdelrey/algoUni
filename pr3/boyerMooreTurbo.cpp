#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

const int MAX_CHAR = 256;

// Функция для заполнения таблицы сдвигов
void preProcessShiftTable(const std::string &pattern, std::vector<int> &shiftTable)
{
	int m = pattern.length();

	// Инициализация таблицы сдвигов
	for (int i = 0; i < MAX_CHAR; i++)
	{
		shiftTable[i] = m;
	}

	// Заполнение таблицы сдвигов для символов в шаблоне
	for (int i = 0; i < m - 1; i++)
	{
		shiftTable[pattern[i]] = m - 1 - i;
	}
}

// Функция для поиска всех вхождений подстроки в строку с использованием алгоритма Бойера-Мура с турбосдвигом
std::vector<int> boyerMooreTurbo(const std::string &text, const std::string &pattern)
{
	std::vector<int> occurrences;
	int n = text.length();
	int m = pattern.length();

	std::vector<int> shiftTable(MAX_CHAR);

	// Заполнение таблицы сдвигов
	preProcessShiftTable(pattern, shiftTable);

	int s = 0; // Сдвиг строки относительно текста

	while (s <= n - m)
	{
		int j = m - 1;

		// Поиск с конца шаблона в тексте
		while (j >= 0 && pattern[j] == text[s + j])
		{
			j--;
		}

		if (j < 0)
		{
			// Найдено вхождение
			occurrences.push_back(s);

			// Турбосдвиг
			s += shiftTable[text[s + m]];
		}
		else
		{
			// Обычный сдвиг
			s += shiftTable[text[s + j]];
		}
	}

	return occurrences;
}

int main()
{
	std::string text = "ABPIUOSFOUPSTNNUARTNVATNAIFISOAIOFTNJHAJFTFANTN";
	std::string pattern = "TN";

	std::vector<int> occurrences = boyerMooreTurbo(text, pattern);

	if (occurrences.empty())
	{
		std::cout << "Подстрока не найдена." << std::endl;
	}
	else
	{
		std::cout << "Вхождения подстроки: ";
		for (int i = 0; i < occurrences.size(); i++)
		{
			std::cout << occurrences[i] << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}