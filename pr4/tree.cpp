#include <iostream>
#include <string>
using namespace std;

// Определение структуры TreeNode, представляющей узел бинарного дерева.
struct TreeNode
{
	string data;	 // Значение, хранимое в узле.
	TreeNode *left;	 // Указатель на левое поддерево.
	TreeNode *right; // Указатель на правое поддерево.

	// Конструктор узла, инициализирующий значение и обнуляющий указатели на поддеревья.
	TreeNode(const string &value) : data(value), left(nullptr), right(nullptr) {}
};

// Определение класса BinarySearchTree, представляющего бинарное дерево.
class BinarySearchTree
{
public:
	TreeNode *root; // Указатель на корень дерева.

	// Конструктор класса, инициализирующий корень как nullptr.
	BinarySearchTree() : root(nullptr) {}

	// Метод для вставки элемента в дерево.
	void Insert(const string &value)
	{
		root = InsertRec(root, value);
	}

	// Метод для симметричного обхода (ин-ордер) бинарного дерева.
	void InorderTraversal(TreeNode *node)
	{
		if (node)
		{
			InorderTraversal(node->left);
			cout << node->data << " ";
			InorderTraversal(node->right);
		}
	}

	// Метод для прямого обхода (пре-ордер) бинарного дерева.
	void PreorderTraversal(TreeNode *node)
	{
		if (node)
		{
			cout << node->data << " ";
			PreorderTraversal(node->left);
			PreorderTraversal(node->right);
		}
	}

	// Метод для вычисления среднего значения в дереве.
	double AverageValue()
	{
		double totalLength = 0.0;
		int count = 0;
		AverageValueRec(root, totalLength, count);
		if (count == 0)
		{
			return 0.0; // Защита от деления на ноль.
		}
		return totalLength / count;
	}

	// Метод для нахождения длины пути до заданного значения.
	int PathLength(const string &value)
	{
		return PathLengthRec(root, value, 0);
	}

private:
	// Рекурсивный метод для вставки элемента.
	TreeNode *InsertRec(TreeNode *root, const string &value)
	{
		if (root == nullptr)
		{
			return new TreeNode(value);
		}

		if (value < root->data)
		{
			root->left = InsertRec(root->left, value);
		}
		else if (value > root->data)
		{
			root->right = InsertRec(root->right, value);
		}

		return root;
	}

	// Рекурсивный метод для вычисления среднего значения.
	void AverageValueRec(TreeNode *node, double &totalLength, int &count)
	{
		if (node)
		{
			totalLength += node->data.length();				  // Добавление длины строки к общей длине.
			count++;										  // Увеличение счетчика строк.
			AverageValueRec(node->left, totalLength, count);  // Рекурсивный вызов для левого поддерева.
			AverageValueRec(node->right, totalLength, count); // Рекурсивный вызов для правого поддерева.
		}
	}

	// Рекурсивный метод для нахождения длины пути.
	int PathLengthRec(TreeNode *node, const string &value, int depth)
	{
		if (node == nullptr)
		{
			return -1; // Если узел не найден, возвращаем -1.
		}

		if (node->data == value)
		{
			return depth; // Если узел с искомым значением найден, возвращаем глубину (длину пути).
		}

		if (value < node->data)
		{
			return PathLengthRec(node->left, value, depth + 1); // Рекурсивный вызов для левого поддерева.
		}
		else
		{
			return PathLengthRec(node->right, value, depth + 1); // Рекурсивный вызов для правого поддерева.
		}
	}
};

// Функция для визуального вывода дерева.
void printTree(TreeNode *root, const string &prefix = "", bool isLeft = false)
{
	if (root != nullptr)
	{
		cout << (prefix + (isLeft ? "|-- " : "'-- ") + root->data) << endl;
		printTree(root->left, prefix + (isLeft ? "|   " : "    "), true);	// Рекурсивный вызов для левого поддерева.
		printTree(root->right, prefix + (isLeft ? "|   " : "    "), false); // Рекурсивный вызов для правого поддерева.
	}
}

int main()
{
	BinarySearchTree tree;
	int length = 0;

	int choice;
	string value;

	do
	{
		// Вывод меню пользователю.
		cout << "1. Вставить элемент" << endl;
		cout << "2. Прямой обход" << endl;
		cout << "3. Симметричный обход" << endl;
		cout << "4. Найти среднее арифметическое" << endl;
		cout << "5. Найти длину пути" << endl;
		cout << "6. Визуальный вывод дерева" << endl;
		cout << "0. Выход" << endl;

		cout << "Выберите действие: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			cout << "Введите значение для вставки: ";
			cin >> value;
			tree.Insert(value); // Вставка значения в дерево.
			break;
		case 2:
			cout << "Прямой обход: ";
			tree.PreorderTraversal(tree.root); // Прямой обход дерева и вывод на экран.
			cout << endl;
			break;
		case 3:
			cout << "Симметричный обход: ";
			tree.InorderTraversal(tree.root); // Симметричный обход дерева и вывод на экран.
			cout << endl;
			break;
		case 4:
			cout << "Среднее арифметическое: " << tree.AverageValue() << endl; // Вывод среднего арифм. значения названия города.
			break;
		case 5:
			cout << "Введите значение для поиска длины пути: ";
			cin >> value;
			length = tree.PathLength(value); // Поиск длины пути до заданного значения.
			if (length != -1)
			{
				cout << "Длина пути до " << value << ": " << length << endl;
			}
			else
			{
				cout << "Значение не найдено в дереве." << endl;
			}
			break;
		case 6:
			cout << "Визуальный вывод дерева:" << endl;
			printTree(tree.root); // Визуальный вывод структуры дерева.
			break;
		case 0:
			break;
		default:
			cout << "Неверный выбор. Попробуйте снова." << endl;
			break;
		}
	} while (choice != 0);

	return 0;
}