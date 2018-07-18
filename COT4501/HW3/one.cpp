#include <iomanip>
#include <iostream>
#include <math.h>

using namespace std;

double fact(double n);

int main()
{
	cout << "\n" << "1.1\n\n" << "n\t" << "Absolute Err\t" << "Relative Err\n";
	
	for(double n = 1; n <= 10; n++)
	{
		double tempA = sqrt(2 * M_PI * n) * pow(n / exp(1.0), n);
		double tempB = fact(n);
		
		double abso = abs(tempA - tempB);
		double rela = abs(abso / tempB);
		
		cout << setprecision(8) << n << "\t" << abso << "\t" << rela << "\n";
	}
	
	cout << "\n";
	return 0;
}

double fact(double n)
{
  return (n == 0 || n == 1) ? 1 : fact(n - 1) * n;
}
