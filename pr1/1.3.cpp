#include <cstdlib>
#include <iostream>
#include <bitset>

using namespace std;
int main()
{

	unsigned int x = 25;
	const int n = sizeof(int) * 8;
	unsigned maska = (1 << n - 1);
	cout << "Initial view of the mask: " << bitset<n>(maska) << endl;
	cout << "Result: ";
	for (int i = 1; i <= n; i++)
	{
		cout << ((x & maska) >> (n - i));
		maska = maska >> 1;
	}

	cout << endl;

	return 0;
}