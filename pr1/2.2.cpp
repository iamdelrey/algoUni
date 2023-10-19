#include <iostream>
#include <vector>

int main()
{
    const int maxNumber = 63;
    int bitArrSize;
    unsigned long long bitArray = 0;

    std::cout << "Enter the number of numbers: ";
    std::cin >> bitArrSize;

    std::cout << "Enter a number (from 0 to 63): " << std::endl;
    std::vector<int> numbers(64, 0);

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
    return 0;
}