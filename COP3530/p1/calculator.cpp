#include <ctype.h>
#include <math.h>

#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <sstream>
#include <unordered_map>

#include "calculator.h"

using namespace std;

bool undeclared = false;
unordered_map<string, int> priority;
unordered_map<string, string> variables;

int main()
{
	priority["+"] = 2;
	priority["-"] = 2;
	priority["*"] = 3;
	priority["/"] = 3;
	priority["^"] = 4;
	variables["PI"] = "3.14169";
	variables["e"] = "2.718";
	
	string value;
	string input;
	
	do
	{
		getline(cin, input);
		
		if( input.compare("quit") == 0 )
		{
			//Quit program when user types in "quit".
			return 0;
		}
		else if( input.find("let") != string::npos )
		{
			//Assign variable to a user-defined name.
			string variableName = input.substr( 4, input.find("=") - 5 );
			variables[variableName] = parseEquation( input.substr(input.find("=") + 2) );
		}
		else
		{
			//Otherwise, just calculate the expression or variable.
			value = parseEquation(input);
			if( undeclared == false ) cout << value;
			cout << "\n\n";
		}
	}
	while(true);
}

bool isOperator(string temp)
{
	return temp == "+" || temp == "-" || temp == "*" || temp == "/" || temp == "^";
}

bool isParan(string temp)
{
	return temp == "(" || temp == ")";
}

string parseEquation(string input)
{
	queue<string> output;
	stack<string> operators;
	stack<string> final;
	
	string temp, temp2, top;
	undeclared = false;
	
	string number = "";
	string variableName = "";
	
	//Traverse the string, one character at a time.
	for( size_t i = 0; i < input.length(); i++ )
	{
		temp = "";
		temp2 = "";
		temp += input[i];
		temp2 += input[i+1];
		
		//Build up the current number substring.
		if( isdigit(input[i]) || temp == "." )
		{
			number += temp;
		}
		//Or build up the current variable name substring.
		else if( isalpha(input[i]) )
		{
			variableName += temp;
		}
		
		//Once we reach the end of the substring (meaning the next character is an operator), push the subtring to the output.
		if( isOperator(temp2) || isParan(temp2) || i == input.length() - 1 )
		{
			//If we have a number, push it to the output.
			if( !number.empty() )
			{
				output.push( number );
				number = "";
			}
			//Or if we have a variable, push that to the output.
			else if( !variableName.empty() )
			{
				if( variableName.compare("sin") == 0 || variableName.compare("cos") == 0 || variableName.compare("log") == 0 )
				{
					operators.push( variableName );
				}
				else
				{
					if( variables.count(variableName) )
					{
						output.push( variables[variableName] );
					}
					else
					{
						cout << "Undeclared-Variable";
						undeclared = true;
						return "";
					}
				}
				variableName = "";
			}
		}
		
		//If we have an operator, check to see where it belongs.
		if( isOperator(temp) )
		{
			if( !operators.empty() )
			{
				while
				(
					isOperator(operators.top()) &&
					(( temp != "^" && priority[temp] < priority[operators.top()] ) ||
					( temp == "^" && priority[temp] < priority[operators.top()] ))
				)
				{
					output.push( operators.top() );
					operators.pop();
				}
				operators.push(temp);
			}
			else operators.push(temp);
		}
		else if( temp == "(" )
		{
			operators.push(temp);
		}
		else if( temp == ")" )
		{
			while( operators.top() != "(" )
			{
				output.push( operators.top() );
				operators.pop();
			}
			operators.pop();
			
			if( !operators.empty() )
			{
				top = operators.top();
				if( top.compare("sin") == 0 || top.compare("cos") == 0 || top.compare("log") == 0 )
				{
					output.push( operators.top() );
					operators.pop();
				}
			}
		}
	}
	
	float left = 0;
	float right = 0;
	float value = 0;
	stringstream ss;
	
	while( !operators.empty() )
	{
		output.push( operators.top() );
		operators.pop();
	}
	
	while( !output.empty() )
	{
		temp = output.front();
		
		if( isOperator(temp) )
		{
			ss << final.top();
			ss >> right;
			ss.clear();
			final.pop();
			
			ss << final.top();
			ss >> left;
			ss.clear();
			final.pop();
			
			if( temp == "+" )
			{
				value = left + right;
				ss << value;
				ss >> temp;
				ss.clear();
			}
			else if( temp == "-" )
			{
				value = left - right;
				ss << value;
				ss >> temp;
				ss.clear();
			}
			else if( temp == "*" )
			{
				value = left * right;
				ss << value;
				ss >> temp;
				ss.clear();
			}
			else if( temp == "/" )
			{
				if( right == 0 )
				{
					cout << "Division-By-Zero";
					undeclared = true;
					return "";
				}
				value = left / right;
				ss << value;
				ss >> temp;
				ss.clear();
			}
			else if( temp == "^" )
			{
				value = pow(left, right);
				ss << value;
				ss >> temp;
				ss.clear();
			}
			
			final.push(temp);
		}
		else if( temp == "sin" )
		{
			ss << final.top();
			ss >> right;
			ss.clear();
			final.pop();
			
			value = sin(right);
			ss << value;
			ss >> temp;
			ss.clear();
		}
		else if( temp == "cos" )
		{
			ss << final.top();
			ss >> right;
			ss.clear();
			final.pop();
			
			value = cos(right);
			ss << value;
			ss >> temp;
			ss.clear();
		}
		else if( temp == "log" )
		{
			ss << final.top();
			ss >> right;
			ss.clear();
			final.pop();
			
			value = log(right);
			ss << value;
			ss >> temp;
			ss.clear();
		}
		else
		{
			final.push(temp);
		}
		output.pop();
	}
	
	return temp;
}
