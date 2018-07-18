#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	stringstream ss;
	string hint, temp, temp2;
	vector<string> row;
	vector<string> column;
	
	int N;
	cin >> hint;
	cin >> N;
	
	
	//Make matrix, get row sequence.
	string matrix[N][N];
	for( int i = 0; i < N; i++ )
	{
		cin >> temp;
		
		int count = 0;
		size_t nPos = temp.find( hint, 0 );
		
		while( nPos != string::npos )
		{
			count++;
			nPos = temp.find( hint, nPos + 1 );
		}
		ss << count;
		ss >> temp2;
		ss.clear();
		row.push_back( temp2 );
		
		for( int j = 0; j < N; j++ )
		{
			matrix[i][j] = temp[j];
		}
	}
	
	
	//Get column sequence.
	for( int j = 0; j < N; j++ )
	{
		temp = "";
		
		for( int i = 0; i < N; i++ )
		{
			temp += matrix[i][j];
		}
		
		int count = 0;
		size_t nPos = temp.find( hint, 0 );
		
		while( nPos != string::npos )
		{
			count++;
			nPos = temp.find( hint, nPos + 1 );
		}
		
		ss << count;
		ss >> temp2;
		ss.clear();
		column.push_back( temp2 );
	}
	
	
	//Make matrix of occurences.
	int occur[N+1][N+1];
	for( int i = 0; i <= row.size(); i++ )
	{
		for( int j = 0; j <= row.size(); j++ )
		{
			if( i == 0 || j == 0 )
			{
				occur[i][j] = 0;
			}
			else if( row.at( i - 1 ) == column.at( j - 1 ) )
			{
				occur[i][j] = occur[i-1][j-1] + 1;
			}
			else
			{
				occur[i][j] = max( occur[i-1][j], occur[i][j-1] );
			}
		}
	}
	
	
	//Get sequence from occurence matrix.
	int i = N;
	int j = N;
	string sequence;
	
	while( i > 0 && j > 0 )
	{
		if( row.at( i - 1 ) == column.at( j - 1 ) )
		{
			ss << row.at( i - 1 );
			ss >> temp;
			ss.clear();
			
			temp += " ";
			sequence.insert( 0, temp );
			
			i--;
			j--;
		}
		else if( occur[i-1][j] > occur[i][j-1] )
		{
			i--;
		}
		else
		{
			j--;
		}
	}
	
	cout << "\n" << sequence << "\n";
	
	return 0;
}
