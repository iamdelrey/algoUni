#include <iostream>
int main()
{
	// system("chcp 1251");
	unsigned char x = 255;	 // 8-разрядное двоичное число 11111111
	unsigned char maska = 1; // 1=00000001 - 8-разрядная маска

	x = x & (~(maska << 4));

	std::cout << "Результат: " << static_cast<int>(x) << std::endl;

	return 0;
}