#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

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

	preProcessShiftTable(pattern, shiftTable);

	int s = 0;			 // Сдвиг строки относительно текста
	int comparisons = 0; // Счетчик сравнений

	while (s <= n - m)
	{
		int j = m - 1;

		while (j >= 0 && pattern[j] == text[s + j])
		{
			j--;
			comparisons++; // Увеличиваем счетчик сравнений
		}

		if (j < 0)
		{
			occurrences.push_back(s);
			s += shiftTable[text[s + m]];
		}
		else
		{
			s += shiftTable[text[s + j]];
		}
		comparisons++; // Увеличиваем счетчик сравнений
	}

	std::cout << "Количество сравнений: " << comparisons << std::endl; // Выводим количество сравнений

	return occurrences;
}

int main()
{
	// std::string text = "ABPIUOSFOUPSTNNUARTNVATNAIFISOAIOFTNJHAJFTFANTNABPIUOSFOUPSTNNUARTNVATNAIFISOAIOFTNJHAJFTFANTN";
	std::string text = "ABFCYABUAB";
	std::string pattern = "AB";

	auto start = std::chrono::high_resolution_clock::now();
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

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	std::cout << "Время выполнения алгоритма: " << duration.count() << " мс" << std::endl;

	return 0;
}