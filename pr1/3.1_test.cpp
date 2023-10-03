#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main()
{

	std::ifstream file("file.txt");

	std::string line, fileContent;

	while(std::getline(file, line))
	{
		fileContent += line;
	}

	std::sort(fileContent.begin(), fileContent.end());
	std::cout<<fileContent;

	file.close();

	std::ofstream outputFile("output.txt");

	if(outputFile.is_open())
	{
		outputFile << fileContent;
	}

	outputFile.close();

	return 0;
}