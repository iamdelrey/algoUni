#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Структура, представляющая предмет с весом и ценностью
struct Item
{
	int weight; // Вес предмета
	int value;	// Ценность предмета
};

// Функция для вывода выбранных предметов в рюкзаке
void findSelectedItems(int W, const vector<Item> &items, const vector<vector<int>> &dp)
{
	int n = items.size();
	int w = W;

	vector<Item> selectedItems;

	// Обратный проход по таблице dp для определения выбранных предметов
	for (int i = n; i > 0 && w > 0; --i)
	{
		if (dp[i][w] != dp[i - 1][w])
		{
			selectedItems.push_back(items[i - 1]);
			w -= items[i - 1].weight;
		}
	}

	// Вывод выбранных предметов
	cout << "Выбранные предметы в рюкзаке:" << endl;
	for (const auto &item : selectedItems)
	{
		cout << "Вес: " << item.weight << ", Ценность: " << item.value << endl;
	}
}

// Функция для решения задачи о рюкзаке с использованием динамического программирования
int knapsack(int W, const vector<Item> &items, int n)
{
	// Создание двумерного вектора для хранения промежуточных результатов
	vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

	// Заполнение таблицы dp
	for (int i = 1; i <= n; ++i)
	{
		for (int w = 1; w <= W; ++w)
		{
			// Вычисление максимальной ценности для текущего веса
			if (items[i - 1].weight <= w)
			{
				// Если предмет может быть включен в рюкзак, выбираем максимум из двух вариантов:
				// 1. Не включать текущий предмет (полученное значение из предыдущей строки)
				// 2. Включить текущий предмет (прибавить его ценность и учесть оставшуюся вместимость)
				dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
			}
			else
			{
				// Если вес предмета больше оставшейся вместимости рюкзака, не включаем его
				dp[i][w] = dp[i - 1][w];
			}
		}
	}

	// Вывод выбранных предметов
	findSelectedItems(W, items, dp);

	// Возвращение максимальной ценности
	return dp[n][W];
}

// Основная функция
int main()
{
	// Установка вместимости рюкзака
	int W = 20;

	// Создание вектора с предметами
	vector<Item> items = {{3, 2}, {4, 1}, {7, 2}, {2, 7}, {6, 10}, {1, 1}, {8, 19}};

	// Получение количества предметов
	int n = items.size();

	// Вычисление и вывод результата
	int result = knapsack(W, items, n);
	cout << "Максимальная ценность: " << result << endl;

	return 0;
}
