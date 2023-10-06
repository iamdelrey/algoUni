#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <sstream>

const int INITIAL_TABLE_SIZE = 10;
const double LOAD_FACTOR_THRESHOLD = 0.75;

struct Item
{
	int code;
	std::string name;
	double price;
};

class HashTable
{
private:
	std::vector<std::list<Item>> table;
	int size;

	int hashFunction(int code)
	{
		return code % size;
	}

	void rehashTable(int newSize)
	{
		std::vector<std::list<Item>> newTable(newSize);

		for (const auto &itemList : table)
		{
			for (const auto &item : itemList)
			{
				int newIndex = hashFunction(item.code);
				newTable[newIndex].push_back(item);
			}
		}

		size = newSize;
		table = std::move(newTable);
	}

public:
	HashTable()
	{
		size = INITIAL_TABLE_SIZE;
		table.resize(size);
	}

	void insertItem(const Item &item)
	{
		double loadFactor = static_cast<double>(getItemCount()) / size;
		if (loadFactor > LOAD_FACTOR_THRESHOLD)
		{
			int newSize = size * 2;
			rehashTable(newSize);
		}

		int index = hashFunction(item.code);
		table[index].push_back(item);
	}

	void removeItem(int code)
	{
		int index = hashFunction(code);

		for (auto it = table[index].begin(); it != table[index].end(); ++it)
		{
			if (it->code == code)
			{
				table[index].erase(it);
				break;
			}
		}
	}

	Item *searchItem(int code)
	{
		int index = hashFunction(code);

		for (auto &item : table[index])
		{
			if (item.code == code)
			{
				return &item;
			}
		}

		return nullptr;
	}

	int getItemCount() const
	{
		int count = 0;

		for (const auto &itemList : table)
		{
			count += itemList.size();
		}

		return count;
	}

	void displayItems()
	{
		for (int i = 0; i < size; ++i)
		{
			for (const auto &item : table[i])
			{
				std::cout << "Код: " << item.code << ", Название: " << item.name << ", Цена: " << item.price << std::endl;
			}
		}
	}
};

void printHelp()
{
	std::cout << "Доступные команды:" << std::endl;
	std::cout << "1. insert <код> <название> <цена> - Вставить товар в хеш-таблицу." << std::endl;
	std::cout << "2. remove <код> - Удалить товар из хеш-таблицы." << std::endl;
	std::cout << "3. search <код>- Найти товар по коду в хеш-таблице." << std::endl;
	std::cout << "4. display - Вывести все товары в хеш-таблице." << std::endl;
	std::cout << "5. help - Вывести список доступных команд." << std::endl;
	std::cout << "6. quit - Выйти из программы." << std::endl;
}

int main()
{
	// system("chcp 1251");
	// system("cls");
	HashTable hashTable;

	std::cout << "Добро пожаловать в программу управления хеш-таблицей" << std::endl;
	printHelp();

	std::string command;
	while (true)
	{
		std::cout << "> ";
		std::getline(std::cin, command);

		if (command.substr(0, 6) == "insert")
		{
			std::istringstream iss(command);
			std::string cmd, codeStr, name, priceStr;
			int code;
			double price;
			if (!(iss >> cmd >> codeStr >> name >> priceStr))
			{
				std::cout << "Ошибка: неверный формат команды." << std::endl;
				continue;
			}

			try
			{
				code = std::stoi(codeStr);
				price = std::stod(priceStr);
				Item item{code, name, price};
				hashTable.insertItem(item);
				std::cout << "Товар успешно добавлен в хеш-таблицу." << std::endl;
			}
			catch (const std::exception &e)
			{
				std::cout << "Ошибка: неверный формат аргументов." << std::endl;
			}
		}
		else if (command.substr(0, 6) == "remove")
		{
			std::istringstream iss(command);
			std::string cmd, codeStr;
			int code;
			if (!(iss >> cmd >> codeStr))
			{
				std::cout << "Ошибка: неверный формат команды." << std::endl;
				continue;
			}

			try
			{
				code = std::stoi(codeStr);
				hashTable.removeItem(code);
				std::cout << "Товар успешно удален из хеш-таблицы." << std::endl;
			}
			catch (const std::exception &e)
			{
				std::cout << "Ошибка: неверный формат аргументов." << std::endl;
			}
		}
		else if (command.substr(0, 6) == "search")
		{
			std::istringstream iss(command);
			std::string cmd, codeStr;
			int code;
			if (!(iss >> cmd >> codeStr))
			{
				std::cout << "Ошибка: неверный формат команды." << std::endl;
				continue;
			}

			try
			{
				code = std::stoi(codeStr);
				Item *item = hashTable.searchItem(code);
				if (item)
				{
					std::cout << "Найден товар: Код: " << item->code << ", Название: " << item->name << ", Цена: " << item->price << std::endl;
				}
				else
				{
					std::cout << "Товар с указанным кодом не найден." << std::endl;
				}
			}
			catch (const std::exception &e)
			{
				std::cout << "Ошибка: неверный формат аргументов." << std::endl;
			}
		}
		else if (command == "display")
		{
			hashTable.displayItems();
		}
		else if (command == "help")
		{
			printHelp();
		}
		else if (command == "quit")
		{
			break;
		}
		else
		{
			std::cout << "Неизвестная команда. Введите 'help' для получения списка команд." << std::endl;
		}
	}

	return 0;
}