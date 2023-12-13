#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

struct NodeHaff
{
	string word = "";
	int chance;
	NodeHaff *to_0;
	NodeHaff *to_1;
};
struct retHaff
{
	string otv;
	map<char, string> encode;
	NodeHaff *now;
};

void Haff(NodeHaff *haff, map<char, string> &encode, string str)
{
	if (haff->word.length() == 1)
	{
		encode[haff->word[0]] = str;
		return;
	}
	else
	{
		Haff(haff->to_0, encode, str + '0');
		Haff(haff->to_1, encode, str + '1');
	}
	return;
}

retHaff coderHaffman(string words)
{
	map<string, int> some_count;
	vector<NodeHaff *> massive_chance_word;
	map<char, string> encode;

	// Заполнения словаря символов количеством их в тексте
	// Заполнение вектора символами
	for (int i = 0; i < words.length(); i++)
	{
		string go = "";
		go += words[i];
		if (some_count.find(go) == some_count.end())
		{
			some_count[go] = 1;
			NodeHaff *now = new NodeHaff;
			now->word = go;
			massive_chance_word.push_back(now);
			encode[go[0]] = "";
		}
		else
		{
			some_count[go]++;
		}
	}
	// Заполение вектора шансами и сумма шансов
	int sum = 0;
	for (int i = 0; i < massive_chance_word.size(); i++)
	{
		massive_chance_word[i]->chance = some_count[massive_chance_word[i]->word];
		sum += massive_chance_word[i]->chance;
	}
	// Сортировка
	int num = 0;
	while (num < massive_chance_word.size() - 1)
	{
		if (massive_chance_word[num]->chance < massive_chance_word[num + 1]->chance)
		{
			NodeHaff *k = massive_chance_word[num];
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

	// Заполнение кодировки
	while (massive_chance_word.size() != 1)
	{
		NodeHaff *nower = new NodeHaff;
		nower->to_0 = massive_chance_word[massive_chance_word.size() - 1];
		nower->to_1 = massive_chance_word[massive_chance_word.size() - 2];
		nower->word = massive_chance_word[massive_chance_word.size() - 2]->word + massive_chance_word[massive_chance_word.size() - 1]->word;
		nower->chance = massive_chance_word[massive_chance_word.size() - 2]->chance + massive_chance_word[massive_chance_word.size() - 1]->chance;
		massive_chance_word[massive_chance_word.size() - 2] = nower;
		massive_chance_word.erase(massive_chance_word.end() - 1);

		int i = massive_chance_word.size() - 1;
		while (i != 0 && massive_chance_word[i]->chance > massive_chance_word[i - 1]->chance)
		{
			NodeHaff *k = massive_chance_word[i];
			massive_chance_word[i] = massive_chance_word[i - 1];
			massive_chance_word[i - 1] = k;
			i--;
		}
	}
	Haff(massive_chance_word[0], encode, "");

	string encoder_word = "";

	for (int i = 0; i < words.length(); i++)
	{
		encoder_word += encode[words[i]];
	}
	retHaff otvet;
	otvet.encode = encode;
	otvet.otv = encoder_word;
	otvet.now = massive_chance_word[0];

	return otvet;
}

string decodeString(NodeHaff *now, const string &encodedString)
{
	string decodedString = "";
	string currentCode;

	NodeHaff *save = now;

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
		if (save->word.length() == 1)
		{
			decodedString += save->word;
			save = now;
		}
	}

	return decodedString;
}

int main()
{
	// Входная строка
	std::string my = "Степанов Антон Вячеславович";
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
	NodeHaff *nower;
	retHaff otvet;
	otvet = coderHaffman(my);
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
	otvet = coderHaffman(my);
	std::cout << "\nКодирование:" << otvet.otv << std::endl;
	std::cout << "\nДекодирование:" << decodeString(otvet.now, otvet.otv) << std::endl;
	return 0;
}