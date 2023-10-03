#include <iostream>

int main()
{
	const int maxNumber = 7;
	int bitArrSize;
	unsigned char bitArray = 0;
	std::cout << "Enter the number of numbers (max 8): ";
	std::cin >> bitArrSize;

	if (bitArrSize < 1 && bitArrSize > 8)
	{
		return -1;
	}

	else
	{
		std::cout << "Enter a numbers (from 0 to 7): " << std::endl;
		int *numbers{new int[bitArrSize]{}};

		for (int i = 0; i < bitArrSize; i++)
		{
			int num;
			std::cin >> num;
			if (num >= 0 && num <= maxNumber)
			{
				numbers[num] = 1;
			}

			else
			{
				std::cout << "The entered number is an incorrect (" << num << ")" << std::endl;
			}
		}

		std::cout << "Sorted set of numbers: " << std::endl;
		for (int i = 0; i <= maxNumber; i++)
		{
			if (numbers[i] == 1)
			{
				std::cout << i << " ";
			}
		}
		std::cout << std::endl;

		delete[] numbers;
	}
	return 0;
}