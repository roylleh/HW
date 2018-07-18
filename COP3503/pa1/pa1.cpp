/*
 * @Programmer: Mohammad Qureshi
 * @Project: Programming Assignment #1
 * @Objective: Create the magic square of an odd integer between 3 and 15 (inclusive) inputted by the user.
 */


#include <iostream>
#include "pa1.h"

using namespace std;

int main()
{
	int n = 0;
	
	cout << "\n";
	cout << "Please enter an odd integer for the magic square (between 3 and 15, inclusive): ";
	cin >> n;
	
	while( cin.fail() || n < 3 || n > 15 || n % 2 == 0 )
	{
		cin.clear();
		cin.ignore();
		cout << "Please enter an odd integer for the magic square (between 3 and 15, inclusive): ";
		cin >> n;
	}
	
	int **mSquare = new int*[n];
	for( int i = 0; i < n; i++ ) mSquare[i] = new int[n];
	for( int i = 0; i < n; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			mSquare[i][j] = 0;
		}
	}
	
	cout << "\n";
	calcSquare( mSquare, n );
	printSquare( mSquare, n );
	printSums( mSquare, n );
	cout << "\n\n";
	
	return 0;
}

void calcSquare( int **mSquare, int n )
{
	int i = 0;
	int j = n / 2;
	int k = 0;
	
	for( k = 1; k <= n * n ; k++ )
	{
		mSquare[i][j] = k;
		
		if( k % n == 0 ) i++;
		else
		{
			if( i == 0 ) i = n - 1;
			else i--;
			
			if( j == (n - 1) ) j = 0;
			else j++;
		}
	}
}

void printSquare( int **mSquare, int n )
{
	cout << "The magic square for n = " << n << " is:\n\n";
	
	for( int i = 0; i < n; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			cout << mSquare[i][j] << "\t";
		}
		
		cout << "\n";
	}
}

void printSums( int **mSquare, int n )
{
	int *r = new int[n]();
	int *c = new int[n]();
	int d[2] = { 0, 0 };
	
	for( int i = 0; i < n; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			r[i] += mSquare[i][j];
			c[j] += mSquare[i][j];
			
			if( i == j ) d[0] += mSquare[i][j];
			if( i == n - j - 1 ) d[1] += mSquare[i][j];
		}
	}
	
	cout << "\n" << "The sums of each row are: ";
	for( int i = 0; i < n; i++ ) cout << r[i] << " ";
	
	cout << "\n" << "The sums of each column are: ";
	for( int i = 0; i < n; i++ ) cout << c[i] << " ";
	
	cout << "\n" << "The sums of each diagonal are: ";
	for( int i = 0; i < 2; i++ ) cout << d[i] << " ";
}
