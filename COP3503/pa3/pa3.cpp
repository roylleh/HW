/*
 * @Programmer: Mohammad Qureshi
 * @Project: Programming Assignment #3
 * @Objective: Use lexical analysis to parse loops and nested loops read in from a file.
 */

#include <deque>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "pa3.h"

using namespace std;

deque<char> KEY;
deque<char> ID;
deque<char> CONST;
deque<char> OPER;
deque<char> DELIM;

deque<string> KEY_WORDS;
deque<string> ID_WORDS;
deque<string> CONST_WORDS;
deque<string> OPER_WORDS;
deque<string> DELIM_WORDS;
deque<string> ERRORS;

int nest = 0;
int begin = 0;
int end = 0;
int lP = 0;
int rP = 0;
int semi = 0;

int main()
{
	string fPath;
	cout << "INPUT> Please enter the file path: ";
	cin >> fPath;
	
	ifstream iFile( fPath.c_str() );
	if( !iFile )
	{
		cout << "Error: Could not open file.";
		return 1;
	}
	
	parse( iFile );
	printResults();
	iFile.close();
	return 0;
}

void parse( ifstream &iFile )
{
	stringstream ss;
	string s;
	string temp;
	char c;
	bool KEY_FLAG = false;
	bool ID_FLAG = false;
	bool CONST_FLAG = false;
	
	while( iFile.get(c) )
	{
		// Keywords
		if( c == ' ' )
		{
			// Do nothing.
		}
		else if( isupper(c) )
		{
			KEY.push_back(c);
			KEY_FLAG = true;
		}
		else if( !isupper(c) && KEY_FLAG == true )
		{
			while( !KEY.empty() )
			{
				ss.str("");
				ss << KEY.front();
				ss >> s;
				temp.append(s);
				KEY.pop_front();
			}
			
			errorCheck( temp );
			temp = "";
			KEY_FLAG = false;
		}
		
		// Identifiers
		else if( islower(c) )
		{
			ID.push_back(c);
			ID_FLAG = true;
		}
		else if( !islower(c) && ID_FLAG == true )
		{
			while( !ID.empty() )
			{
				ss.str("");
				ss << ID.front();
				ss >> s;
				temp.append(s);
				ID.pop_front();
			}
			
			temp = "";
			ID_FLAG = false;
		}
		
		// Constants
		else if( isdigit(c) )
		{
			CONST.push_back(c);
			CONST_FLAG = true;
		}
		else if( !isdigit(c) && CONST_FLAG == true )
		{
			while( !CONST.empty() )
			{
				ss.str("");
				ss << CONST.front();
				ss >> s;
				temp.append(s);
				CONST.pop_front();
			}
			
			temp = "";
			CONST_FLAG = false;
		}
		
		// Operators
		else if( c == '+' )
		{
			ss.str("");
			ss << c;
			ss >> s;
			OPER_WORDS.push_back(s);
		}
		else if( c == '-' )
		{
			ss.str("");
			ss << c;
			ss >> s;
			OPER_WORDS.push_back(s);
		}
		else if( c == '*' )
		{
			ss.str("");
			ss << c;
			ss >> s;
			OPER_WORDS.push_back(s);
		}
		else if( c == '/' )
		{
			ss.str("");
			ss << c;
			ss >> s;
			OPER_WORDS.push_back(s);
		}
		else if( c == '=' )
		{
			ss.str("");
			ss << c;
			ss >> s;
			OPER_WORDS.push_back(s);
			semi = 1;
		}
		
		// Delimiters
		else if( c == '(' )
		{
			ss.str("");
			ss << c;
			ss >> s;
			DELIM_WORDS.push_back(s);
			lP++;
		}
		else if( c == ')' )
		{
			ss.str("");
			ss << c;
			ss >> s;
			DELIM_WORDS.push_back(s);
			rP++;
		}
		else if( c == ';' )
		{
			ss.str("");
			ss << c;
			ss >> s;
			DELIM_WORDS.push_back(s);
			if( semi == 1 ) semi = 0;
		}
		else if( c == ',' )
		{
			ss.str("");
			ss << c;
			ss >> s;
			DELIM_WORDS.push_back(s);
		}
	}
}

void errorCheck( string temp )
{
	if( temp.compare("BEGIN") == 0 )
	{
		KEY_WORDS.push_back( temp );
		begin++;
	}
	else if( temp.compare("END") == 0 )
	{
		KEY_WORDS.push_back( temp );
		end++;
	}
	else if( temp.compare("FOR") == 0 )
	{
		KEY_WORDS.push_back( temp );
		nest++;
	}
	else if( temp.compare("WHILE") == 0 )
	{
		KEY_WORDS.push_back( temp );
		nest++;
	}
	else if( temp.compare("IF") == 0 )
	{
		KEY_WORDS.push_back( temp );
	}
	else if( temp.compare("ELSEIF") == 0 )
	{
		KEY_WORDS.push_back( temp );
	}
	else if( temp.compare("ELSE") == 0 )
	{
		KEY_WORDS.push_back( temp );
	}
	else ERRORS.push_back( temp );
}

void printResults()
{
	cout << "\nOUTPUT> The number of nested loops is: " << nest;
	
	cout << "\nKeywords: ";
	while( !KEY_WORDS.empty() )
	{
		cout << KEY_WORDS.front() << " ";
		KEY_WORDS.pop_front();
	}
	
	cout << "\nIdentifiers: ";
	while( !ID_WORDS.empty() )
	{
		cout << ID_WORDS.front() << " ";
		ID_WORDS.pop_front();
	}
	
	cout << "\nConstants: ";
	while( !CONST_WORDS.empty() )
	{
		cout << CONST_WORDS.front() << " ";
		CONST_WORDS.pop_front();
	}
	
	cout << "\nOperators: ";
	while( !OPER_WORDS.empty() )
	{
		cout << OPER_WORDS.front() << " ";
		OPER_WORDS.pop_front();
	}
	
	cout << "\nDelimiters: ";
	while( !DELIM_WORDS.empty() )
	{
		cout << DELIM_WORDS.front() << " ";
		DELIM_WORDS.pop_front();
	}
	
	cout << "\n";
	if( begin > end ) cout << "\nError: Missing \"END\"";
	if( begin < end ) cout << "\nError: Missing \"BEGIN\"";
	if( lP > rP ) cout << "\nError: Missing \")\"";
	if( lP < rP ) cout << "\nError: Missing \"(\"";
	if( semi > 0 ) cout<< "\nError: Missing \";\"";
	while( !ERRORS.empty() )
	{
		cout << "\nError: " << ERRORS.front() << " ";
		ERRORS.pop_front();
	}
	cout << "\n";
}
