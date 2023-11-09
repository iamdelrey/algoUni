#include <iostream>
#include <vector>

const int INF = 1e9; // Максимальное значение, используемое для представления отсутствия ребра

// Структура для представления ребра графа
struct Edge
{
	int from, to, weight;
};

// Функция для добавления ребра в список рёбер
void addEdge(std::vector<Edge> &edges, int from, int to, int weight)
{
	Edge edge = {from, to, weight};
	edges.push_back(edge);
}

// Реализация алгоритма Беллмана-Форда
void bellmanFord(std::vector<Edge> &edges, int numVertices, int source)
{
	std::vector<int> distance(numVertices, INF); // Создаем массив для хранения расстояний до вершин, инициализируем бесконечностью
	distance[source] = 0;						 // Расстояние до начальной вершины устанавливаем в 0

	// Выполняем итерации для обновления расстояний (не более numVertices - 1 раз)
	for (int i = 0; i < numVertices - 1; ++i)
	{
		for (const Edge &edge : edges)
		{ // Проходим по всем рёбрам
			// Если нашли более короткий путь до вершины через текущую вершину, обновляем расстояние
			if (distance[edge.from] + edge.weight < distance[edge.to])
			{
				distance[edge.to] = distance[edge.from] + edge.weight;
			}
		}
	}

	// Проверяем наличие циклов с отрицательными весами
	for (const Edge &edge : edges)
	{
		if (distance[edge.from] + edge.weight < distance[edge.to])
		{
			std::cout << "Граф содержит цикл с отрицательным весом!" << std::endl;
			return;
		}
	}

	// Вывод кратчайших расстояний от исходной вершины до остальных
	std::cout << "Кратчайшие расстояния от вершины " << source << ":" << std::endl;
	for (int i = 0; i < numVertices; ++i)
	{
		std::cout << "Вершина " << i << ": " << distance[i] << std::endl;
	}
}

int main()
{
	int numVertices, numEdges;
	std::cout << "Введите количество вершин и рёбер графа: ";
	std::cin >> numVertices >> numEdges;

	std::vector<Edge> edges;
	std::cout << "Введите рёбра и их веса (\"от номера вершины\"  \"до номера вершины\" вес):" << std::endl;
	for (int i = 0; i < numEdges; ++i)
	{
		int from, to, weight;
		std::cin >> from >> to >> weight;
		addEdge(edges, from, to, weight);
	}

	int source;
	std::cout << "Введите начальную вершину: ";
	std::cin >> source;

	bellmanFord(edges, numVertices, source);

	return 0;
}