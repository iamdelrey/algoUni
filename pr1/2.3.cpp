#include <iostream>

int main()
{
    const int maxNumber = 63;
    int bitArrSize;
    const int arraySize = maxNumber / 8 + 1;
    unsigned char bitArray[arraySize] = {0};

    std::cout << "Enter the number of numbers: ";
    std::cin >> bitArrSize;
    std::cout << "Enter a number (from 0 to 63) :" << std::endl;
    for (int i = 0; i < bitArrSize; i++)
    {
        int num;
        std::cin >> num;
        if (num >= 0 && num <= maxNumber)
        {
            int byteIndex = num / 8;
            int bitIndex = num % 8;
            bitArray[byteIndex] |= (1 << bitIndex);
        }
        else
        {
            std::cout << "The entered number is an incorrect (" << num << ")" << std::endl;
        }
    }
    std::cout << "Sorted set of numbers: " << std::endl;
    for (int i = 0; i <= maxNumber; i++)
    {
        int byteIndex = i / 8;
        int bitIndex = i % 8;
        if ((bitArray[byteIndex] & (1 << bitIndex)) != 0)
        {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
    return 0;
}