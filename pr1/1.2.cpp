#include <iostream>

int main()
{
    unsigned char x = 128;
    unsigned char maska = 1;

    x = x | (maska << 6);

    std::cout << "Result: " << static_cast<int>(x) << std::endl;

    return 0;
}