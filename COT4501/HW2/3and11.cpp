#include <iostream>
#include <math.h>

using namespace std;

void doMath( int i );

int main()
{
	cout << "\n";
	
	for( int i = 1; i <= 6; i++ )
	{
		doMath(i);
		cout << "\n";
	}
}

void doMath( int i )
{
	double x = 1;
	double temp;
	
	for( double h = 4; h <= 32; h = h * 2 )
	{
		cout << h << "\t";
		temp = h;
		h = pow( h, -1 );
		
		switch(i)
		{
			case 1:
				cout << ( sqrt(x+h + 1) - sqrt(x + 1) ) * temp << "\t";
				cout << ( sqrt(x+h + 1) - sqrt(x-h + 1) ) * ( temp / 2 ) << "\t";
				break;
			case 2:
				cout << ( atan(x+h) - atan(x) ) * temp << "\t";
				cout << ( atan(x+h) - atan(x-h) ) * ( temp / 2 ) << "\t";
				break;
			case 3:
				cout << ( sin(M_PI * (x+h)) - sin(M_PI * x) ) * temp << "\t";
				cout << ( sin(M_PI * (x+h)) - sin(M_PI * (x-h)) ) * ( temp / 2 ) << "\t";
				break;
			case 4:
				cout << ( exp((x+h) * -1) - exp(x * -1) ) * temp << "\t";
				cout << ( exp((x+h) * -1) - exp((x-h) * -1) ) * ( temp / 2 ) << "\t";
				break;
			case 5:
				cout << ( log(x+h) - log(x) ) * temp << "\t";
				cout << ( log(x+h) - log(x-h) ) * ( temp / 2 ) << "\t";
				break;
			case 6:
				cout << ( 8*atan(M_PI/4 + h) - 8*atan(M_PI/4 - h) - atan(M_PI/4 + 2*h) + atan(M_PI/4 - 2*h) ) * ( temp / 12 ) << "\t";
				break;
		}
		
		h = temp;
		cout << "\n";
	}
}
