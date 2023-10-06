#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>

int main()
{
	// system("chcp 1251");
	// system ("cls");
	auto start_time = std::chrono::high_resolution_clock::now();
	const int MAX_NUM = 10000000;
	const int BITSET_SIZE = MAX_NUM + 1;
	std::vector<unsigned char> bitArray((BITSET_SIZE + 7) / 8, 0);
	int byte_size = BITSET_SIZE / 8;

	// Получение размера памяти, занимаемой битовым массивом
	size_t memory_usage_bytes = sizeof(bitArray);

	// Преобразование байтов в мегабайты (1 МБ = 1024 КБ = 1024 * 1024 байт)
	double memory_usage_megabytes = static_cast<double>(memory_usage_bytes) / (1024 * 1024);

	std::ifstream inputFile("file.txt");
	if (!inputFile)
	{
		std::cerr << "Ошибка при открытии файла" << std::endl;
		return 1;
	}
	std::string line;

	while (getline(inputFile, line))
	{
		int num = stoi(line);
		int byteIndex = num / 8;
		int bitIndex = 7 - (num % 8);
		bitArray[byteIndex] = bitArray[byteIndex] | (1 << bitIndex);
	}

	inputFile.close();
	std::ofstream outputFile("fileOutput.txt");

	if (!outputFile)
	{
		std::cerr << "Ошибка при открытии файла" << std::endl;
		return 1;
	}

	for (int i = 0; i <= 10000000; i++)
	{
		int byteIndex = i / 8;
		int bitIndex = 7 - (i % 8);
		if (bitArray[byteIndex] & (1 << bitIndex))
		{
			outputFile << i << std::endl;
		}
	}
	outputFile.close();

	auto end_time = std::chrono::high_resolution_clock::now();

	// Вычисление разницы между начальным и конечным временем
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout << "Время выполнения программы: " << duration.count() << " миллисекунд" << std::endl;
	std::cout << "Размер битового массива в байтах: " << byte_size << " байт " << std::endl;
	std::cout << "Объем оперативной памяти, занимаемый битовым массивом: " << memory_usage_bytes << " байт" << std::endl;
	std::cout << "Объем оперативной памяти, занимаемый битовым массивом: " << memory_usage_megabytes << " M" << std::endl;
	return 0;
}