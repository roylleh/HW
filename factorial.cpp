//Issue during interview: Not remembering math manipulation techniques. Honestly it's a lot easier to just use Java or Python's built in Math capabilities.
//Space: O(n)
//Time: O(n)

#include <iostream>
using namespace std;

int multiply(int i, int num[], int digits)
{
	int carry = 0;

	for (int j = 0; j < digits; j++)
	{
		int temp = num[j] * i + carry;
		num[j] = temp % 10;
		carry = temp / 10;
	}

	while (carry)
	{
		num[digits] = carry % 10;
		carry /= 10;
		digits++;
	}

	return digits;
}

void fact(int n)
{
	int num[n * 10];
	num[0] = 1;

	int digits = 1;
	for (int i = 2; i <= n; i++)
		digits = multiply(i, num, digits);

	for (int i = digits - 1; i >= 0; i--)
		cout << num[i];
}

int main()
{
	fact(100);
	return 0;
}