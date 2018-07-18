#include <iostream>

int main()
{
	int k = 0;
	int n;
	std::cin >> n;

	for( int i = 1; i <= n; i++ )
	{
		if( n % i == 0 )
		{
			std::cout << i;
			if( i != n ) std::cout << ", ";
			k++;
		}
	}

	std::cout << "\n";
	if( k == 2 ) std::cout << "Prime!\n";
	else std::cout << "Not Prime!\n";

	return 0;
}
