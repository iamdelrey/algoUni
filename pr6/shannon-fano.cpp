#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

// Структура для представления символа и его вероятности появления
struct chance_word
{
	int chance; // Вероятность появления символа
	char word;	// Символ
};

// Структура узла для построения бинарного дерева
struct Node
{
	char name = 0; // Символ в узле (0, если узел не представляет символ)
	Node *to_0;	   // Указатель на левого потомка
	Node *to_1;	   // Указатель на правого потомка
};

// Структура для хранения результата кодирования
struct ret
{
	std::string otv;					// Закодированная строка
	std::map<char, std::string> encode; // Словарь кодов символов
	Node *now;							// Корень бинарного дерева
};

// Рекурсивная функция для построения бинарного дерева по алгоритму Фанно
Node *noder(std::map<char, std::string> &encode, std::vector<chance_word> &massive_chance_word, int sum, int start_size, int stop_size)
{
	int now_sum = 0;
	int stop = -1;

	// Если диапазон состоит из одного элемента, создаем и возвращаем узел
	if (stop_size - start_size == 1)
	{
		Node *now = new Node;
		now->name = massive_chance_word[start_size].word;
		return now;
	}

	// Разбиваем диапазон на две части, добавляя бит '1' или '0' к кодам символов
	for (int i = start_size; i < stop_size; i++)
	{
		if (now_sum >= sum / 2)
		{
			if (stop == -1)
			{
				stop = i;
			}
			encode[massive_chance_word[i].word] += '1';
		}
		else
		{
			encode[massive_chance_word[i].word] += '0';
			now_sum += massive_chance_word[i].chance;
		}
	}

	// Рекурсивно строим левое и правое поддерево
	Node *now = new Node;
	now->to_0 = noder(encode, massive_chance_word, now_sum, start_size, stop);
	now->to_1 = noder(encode, massive_chance_word, sum - now_sum, stop, stop_size);

	return now;
}

// Функция для выполнения кодирования методом Фанно
ret coderFanno(std::string words)
{
	std::map<char, int> some_count;				  // Словарь для подсчета встреч символов
	std::vector<chance_word> massive_chance_word; // Вектор структур chance_word
	std::map<char, std::string> encode;			  // Словарь для хранения кодов символов

	// Подсчитываем количество встреч каждого символа в строке
	for (int i = 0; i < words.length(); i++)
	{
		if (some_count.find(words[i]) == some_count.end())
		{
			some_count[words[i]] = 1;
			chance_word now;
			now.word = words[i];
			massive_chance_word.push_back(now);
			encode[words[i]] = "";
		}
		else
		{
			some_count[words[i]]++;
		}
	}

	int sum = 0;
	// Суммируем вероятности символов и инициализируем структуру massive_chance_word
	for (int i = 0; i < massive_chance_word.size(); i++)
	{
		massive_chance_word[i].chance = some_count[massive_chance_word[i].word];
		sum += massive_chance_word[i].chance;
	}

	// Сортируем символы по убыванию вероятности
	int num = 0;
	while (num < massive_chance_word.size() - 1)
	{
		if (massive_chance_word[num].chance < massive_chance_word[num + 1].chance)
		{
			chance_word k = massive_chance_word[num];
			massive_chance_word[num] = massive_chance_word[num + 1];
			massive_chance_word[num + 1] = k;
			if (num != 0)
			{
				num--;
			}
		}
		else
		{
			num++;
		}
	}

	// Создаем корень дерева и вызываем функцию построения дерева
	Node *nower;
	nower = noder(encode, massive_chance_word, sum, 0, massive_chance_word.size());

	// Кодируем входную строку
	std::string encoder_word = "";
	for (int i = 0; i < words.length(); i++)
	{
		encoder_word += encode[words[i]];
	}

	// Заполняем структуру ret результатами
	ret otvet;
	otvet.encode = encode;
	otvet.otv = encoder_word;
	otvet.now = nower;

	return otvet;
}

// Функция для декодирования строки на основе бинарного дерева
std::string decodeString(Node *now, const std::string &encodedString)
{
	std::string decodedString = "";
	std::string currentCode;

	Node *save = now;

	// Проходим по бинарной строке и декодируем символы
	for (char c : encodedString)
	{
		if (c == '0')
		{
			save = save->to_0;
		}
		else
		{
			save = save->to_1;
		}
		if (save->name != 0)
		{
			decodedString += save->name;
			save = now;
		}
	}

	return decodedString;
}

int main()
{
	// Входная строка
	std::string my = "Зуба зуба, зуба зуба, Зуба дони дони мэ, А шарли буба раз два три, А ми раз два три замри.";

	// Подсчет повторений каждого символа
	std::map<char, int> some_count;
	for (int i = 0; i < my.length(); i++)
	{
		if (some_count.find(my[i]) == some_count.end())
		{
			some_count[my[i]] = 1;
		}
		else
		{
			some_count[my[i]]++;
		}
	}

	// Создаем корень дерева и вызываем функцию построения дерева
	Node *nower;
	ret otvet;
	otvet = coderFanno(my);
	nower = otvet.now;

	// Сортировка символов по убыванию повторений
	std::vector<std::pair<char, int>> sorted_counts(some_count.begin(), some_count.end());
	std::sort(sorted_counts.begin(), sorted_counts.end(),
			  [](const std::pair<char, int> &a, const std::pair<char, int> &b)
			  {
				  return a.second > b.second;
			  });

	// Создаем вектор пар для сортировки по кодам
	std::vector<std::pair<std::string, std::pair<char, int>>> sorted_with_codes;
	for (const auto &entry : sorted_counts)
	{
		sorted_with_codes.push_back(std::make_pair(otvet.encode[entry.first], std::make_pair(entry.first, entry.second)));
	}

	// Сортируем вектор пар по кодам
	std::sort(sorted_with_codes.begin(), sorted_with_codes.end(),
			  [](const auto &a, const auto &b)
			  {
				  return a.first.length() < b.first.length() || (a.first.length() == b.first.length() && a.first < b.first);
			  });

	// Вывод информации о повторениях символов с добавлением кодов
	std::cout << "Исходная фраза: " << my << std::endl;
	std::cout << std::setw(10) << "Код" << std::setw(10) << "Символ" << std::setw(15) << "Повторения" << std::endl;
	std::cout << "--------------------------------------" << std::endl;
	int total_count = 0;
	for (const auto &entry : sorted_with_codes)
	{
		std::cout << std::setw(10) << entry.first << std::setw(10) << entry.second.first << std::setw(15) << entry.second.second << std::endl;
		total_count += entry.second.second;
	}

	std::cout << "--------------------------------------" << std::endl;
	std::cout << std::setw(20) << "Итого" << std::setw(15) << total_count << std::endl;

	// Кодирование и декодирование строки
	otvet = coderFanno(my);

	std::cout << "\nКодирование:" << otvet.otv << std::endl;
	std::cout << "\nДекодирование:" << decodeString(otvet.now, otvet.otv) << std::endl;

	return 0;
}
