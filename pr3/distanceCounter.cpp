#include <iostream>
#include <string>
#include <vector>
#include <chrono>

// Функция для разделения предложения на слова
std::vector<std::string> splitSentence(const std::string &sentence)
{
	std::vector<std::string> words;
	size_t startPos = 0;
	size_t endPos = 0;

	// Разбиваем предложение на слова по пробелам
	while ((endPos = sentence.find(" ", startPos)) != std::string::npos)
	{
		words.push_back(sentence.substr(startPos, endPos - startPos));
		startPos = endPos + 1;
	}
	words.push_back(sentence.substr(startPos));

	return words;
}

// Функция для вычисления расстояния между двумя словами
int wordDistance(const std::string &word1, const std::string &word2)
{
	int distance = 0;
	size_t minSize = std::min(word1.size(), word2.size());

	// Вычисляем расстояние между словами путем сравнения символов
	for (size_t i = 0; i < minSize; ++i)
	{
		if (word1[i] != word2[i])
		{
			++distance;
		}
	}

	// Добавляем разницу в длине слов
	distance += std::abs(static_cast<int>(word1.size()) - static_cast<int>(word2.size()));

	return distance;
}

// Функция для нахождения ближайших слов в предложении
std::pair<std::string, std::string> findClosestWords(const std::vector<std::string> &words)
{
	int minDistance = words[0].size() + words[1].size();
	std::pair<std::string, std::string> closestWords;

	// Находим ближайшие слова, сравнивая расстояния между всеми парами слов
	for (size_t i = 0; i < words.size(); ++i)
	{
		for (size_t j = i + 1; j < words.size(); ++j)
		{
			int distance = wordDistance(words[i], words[j]);
			if (distance < minDistance)
			{
				minDistance = distance;
				closestWords = std::make_pair(words[i], words[j]);
			}
		}
	}

	return closestWords;
}

int main()
{
	// Установка кодовой страницы для корректного ввода/вывода кириллических символов
	std::string sentence;
	std::cout << "Введите предложение: ";
	std::getline(std::cin, sentence);

	auto start = std::chrono::high_resolution_clock::now();
	std::vector<std::string> words = splitSentence(sentence);

	if (words.size() < 2)
	{
		std::cout << "В предложении должно быть как минимум два слова." << std::endl;
		return 1;
	}

	// Находим и выводим ближайшие слова и их расстояние
	std::pair<std::string, std::string> closestWords = findClosestWords(words);

	std::cout << "Ближайшие слова: \"" << closestWords.first << "\" и \"" << closestWords.second << "\" с расстоянием " << wordDistance(closestWords.first, closestWords.second) << std::endl;

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	std::cout << "Время выполнения алгоритма: " << duration.count() << " мс" << std::endl;

	return 0;
}