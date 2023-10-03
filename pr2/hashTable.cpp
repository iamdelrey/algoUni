#include <iostream>
#include <vector>
#include <string>

struct Product
{
	int code;
	std::string name;
	double price;

	Product(int c, const std::string &n, double p) : code(c), name(n), price(p) {}
};

class HashTable
{
private:
	static const int INITIAL_SIZE = 100;
	static const double LOAD_FACTOR_THRESHOLD;

	std::vector<std::vector<Product>> table;
	int size;

	int hashFunction(int code)
	{
		return code % table.size();
	}

	void resizeTable()
	{
		int newSize = table.size() * 2; // Удвоение размера таблицы
		std::vector<std::vector<Product>> newTable(newSize);

		// Перехеширование существующих элементов
		for (const auto &chain : table)
		{
			for (const Product &product : chain)
			{
				int index = product.code % newSize;
				newTable[index].push_back(product);
			}
		}

		table = std::move(newTable);
	}

	void checkResize()
	{
		double loadFactor = static_cast<double>(size) / table.size();
		if (loadFactor >= LOAD_FACTOR_THRESHOLD)
		{
			resizeTable();
		}
	}

public:
	HashTable() : size(0)
	{
		table.resize(INITIAL_SIZE);
	}

	void insert(const Product &product)
	{
		checkResize();
		int index = hashFunction(product.code);
		table[index].push_back(product);
		size++;
	}

	Product *search(int code)
	{
		int index = hashFunction(code);
		for (Product &product : table[index])
		{
			if (product.code == code)
			{
				return &product;
			}
		}
		return nullptr;
	}

	bool remove(int code)
	{
		int index = hashFunction(code);
		for (auto it = table[index].begin(); it != table[index].end(); ++it)
		{
			if (it->code == code)
			{
				table[index].erase(it);
				size--;
				return true;
			}
		}
		return false;
	}

	void printAll()
	{
		for (const std::vector<Product> &chain : table)
		{
			for (const Product &product : chain)
			{
				std::cout << "Code: " << product.code << ", Name: " << product.name << ", Price: " << product.price << std::endl;
			}
		}
	}
};

const double HashTable::LOAD_FACTOR_THRESHOLD = 0.75;

int main()
{
	HashTable productTable;

	productTable.insert(Product(123456, "Product1", 10.0));
	productTable.insert(Product(789012, "Product2", 20.0));
	productTable.insert(Product(345678, "Product3", 30.0));
	productTable.insert(Product(901234, "Product4", 40.0));
	productTable.insert(Product(567890, "Product5", 50.0));

	while (true)
	{
		std::cout << "Введите команду (1 - добавить товар, 2 - найти товар, 3 - удалить товар, 4 - вывести все товары, 0 - выход): ";
		int choice;
		std::cin >> choice;

		switch (choice)
		{
		case 1:
		{
			int code;
			std::string name;
			double price;
			std::cout << "Введите код товара: ";
			std::cin >> code;
			std::cout << "Введите название товара: ";
			std::cin >> name;
			std::cout << "Введите цену товара: ";
			std::cin >> price;
			productTable.insert(Product(code, name, price));
			std::cout << "Товар добавлен." << std::endl;
			break;
		}
		case 2:
		{
			int code;
			std::cout << "Введите код товара для поиска: ";
			std::cin >> code;
			Product *searchedProduct = productTable.search(code);
			if (searchedProduct)
			{
				std::cout << "Найден товар: Code: " << searchedProduct->code << ", Name: " << searchedProduct->name << ", Price: " << searchedProduct->price << std::endl;
			}
			else
			{
				std::cout << "Товар с указанным кодом не найден." << std::endl;
			}
			break;
		}
		case 3:
		{
			int code;
			std::cout << "Введите код товара для удаления: ";
			std::cin >> code;
			if (productTable.remove(code))
			{
				std::cout << "Товар с указанным кодом удален." << std::endl;
			}
			else
			{
				std::cout << "Товар с указанным кодом не найден для удаления." << std::endl;
			}
			break;
		}
		case 4:
		{
			std::cout << "Все товары:" << std::endl;
			productTable.printAll();
			break;
		}
		case 0:
			return 0;
		default:
			std::cout << "Неверная команда. Попробуйте снова." << std::endl;
			break;
		}
	}

	return 0;
}