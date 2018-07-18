/*
 * @Programmer: Mohammad Qureshi
 * @Project: Programming Assignment #2
 * @Objective: Simulate OS memory management using linked lists.
 */

#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include "pa2.h"

using namespace std;

const int pages = 32;
const int pageSize = 4;
char *algo;
LinkedList memory;

int main( int argc, char *argv[] )
{
	algo = argv[1];
	int choice = 0;

	if( argc != 2 || (strcasecmp(algo, "best") != 0 && strcasecmp(algo, "worst") != 0) )
	{
		cout << "Error: Please provide either \"best\" or \"worst\" as a command line argument.\n";
		return 0;
	}
	
	for( int i = 0; i < pages; i++ ) memory.insert( i, "Free", 0 );

	cout << "\nUsing " << algo << " fit algorithm.\n\n";
	cout << "\t1. Add Program\n";
	cout << "\t2. End Program\n";
	cout << "\t3. Check Fragmentation\n";
	cout << "\t4. View Memory\n";
	cout << "\t5. Exit";
	
	while( (choice = procChoice()) != 5 )
	{
		switch( choice )
		{
			case 1: memory.addProgram(); break;
			case 2: memory.endProgram(); break;
			case 3: memory.checkFrag(); break;
			case 4: memory.print(); break;
		}
	}
	
	return 0;
}


int procChoice()
{
	string input = "";
	int choice = 0;
	
	cout << "\n\nChoice: ";
	while( true )
	{
		getline( cin, input );
		stringstream convert( input );
		if( convert >> choice && choice >= 1 && choice <= 5 ) break;
		else cout << "Please enter your choice as an integer between 1 and 5: ";
	}
	
	return choice;
}


Node::Node( int num, char *name, int size )
{
	this->num = num;
	this->name = name;
	this->size = size;
	this->next = NULL;
}


LinkedList::LinkedList()
{
	this->head = NULL;
}


void LinkedList::insert( int num, char *name, int size )
{
	Node *newNode = new Node( num, name, size );
	if( head == NULL )
	{
		head = newNode;
		return;
	}
	
	Node *temp = head;
	while( temp->next != NULL )
	{
		temp = temp->next;
	}
	temp->next = newNode;
}


void LinkedList::addProgram()
{
	string input = "";
	int size = 0;
	
	cout << "Program Name: ";
	getline( cin, input );
	if( input.compare("Free") == 0 )
	{
		cout << "Please enter a name other than \"Free\"";
		return;
	}
	char *name = new char[input.size() + 1];
	copy( input.begin(), input.end(), name );
	
	cout << "Program Size (KB): ";
	while( true )
	{
		getline( cin, input );
		stringstream convert( input );
		if( convert >> size && size >= 1 ) break;
		else cout << "Please enter the size of your program as an integer in KB: ";
	}
	
	Node *temp = head;
	while( temp->next != NULL )
	{
		if( strcmp(temp->name, name) == 0 )
		{
			cout << "\nError: " << name << " is already running.";
			return;
		}
		temp = temp->next;
	}
	
	int reqPages = size / pageSize;
	int frag = size % pageSize;
	if( frag > 0 ) reqPages++;
	
	int num = 0;
	if( size > pages * pageSize || (num = memory.findHole( algo, reqPages )) < 0 )
	{
		cout << "\nError: Not enough memory for " << name;
		return;
	}
	
	temp = head;
	while( temp->num != num )
	{
		temp = temp->next;
	}
	cout << "\n" << name << " has been added. " << reqPages << " page(s) used.";
	
	while( reqPages > 0 )
	{
		temp->name = name;
		if( reqPages == 1 && frag > 0 ) temp->size = frag;
		else temp->size = 4;
		temp = temp->next;
		reqPages--;
	}
}


int LinkedList::findHole( char *algo, int reqPages )
{
	int num = -1;
	int usedPages = 0;
	
	if( strcasecmp(algo, "best") == 0 )
	{
		Node *temp = head;
		while( temp->next != NULL )
		{
			if( strcasecmp(temp->name, "Free") == 0 )
			{
				if( num < 0 ) num = temp->num;
				usedPages++;
			}
			else
			{
				num = -1;
				usedPages = 0;
			}
			
			if( usedPages == reqPages ) return num;
			temp = temp->next;
		}
		
		return num;
	}
	else
	{
		int lastNum = -1;
		int lastPages = 0;
		Node *temp = head;

		while( temp->next != NULL )
		{
			if( strcasecmp(temp->name, "Free") == 0 )
			{
				if( num < 0 ) num = temp->num;
				usedPages++;
			}
			else
			{
				num = -1;
				usedPages = 0;
			}
			
			if( usedPages >= reqPages && usedPages > lastPages )
			{
				lastPages = usedPages;
				lastNum = num;
			}
			temp = temp->next;
		}
		
		return lastNum;
	}
}


void LinkedList::endProgram()
{
	string input = "";
	bool found = false;
	int pages = 0;
	
	cout << "Program Name: ";
	getline( cin, input );
	if( input.compare("Free") == 0 )
	{
		cout << "Please enter a name other than \"Free\"";
		return;
	}
	char *name = new char[input.size() + 1];
	copy( input.begin(), input.end(), name );
	
	Node *temp = head;
	while( temp->next != NULL )
	{
		if( strcasecmp(temp->name, name) == 0 )
		{
			temp->name = "Free";
			temp->size = 0;
			found = true;
			pages++;
		}
		
		temp = temp->next;
		if( temp->next == NULL && strcasecmp(temp->name, "Free") != 0 ) pages++;
	}
	
	if( !found ) cout << "\nError: " << name << " is not currently running.";
	else cout << "\n" << name << " has been ended. " << pages << " page(s) reclaimed.";
}


void LinkedList::checkFrag()
{
	Node *temp = head;
	int num = -1;
	int frags = 0;
	
	while( temp->next != NULL )
	{
		if( strcasecmp(temp->name, "Free") != 0 ) num = temp->num;
		temp = temp->next;
	}
	
	temp = head;
	for( int i = 0; i < num; i++ )
	{
		if( temp->size < 4 ) frags++;
		temp = temp->next;
	}
	cout << "\n" << frags << " fragment(s) detected.";
}


void LinkedList::print()
{
	int i = 1;
	Node *temp = head;
	
	cout << "\n";
	while( temp->next != NULL )
	{
		cout << temp->name << " (" << temp->size << " KB)" << "\t";
		if( i % 8 == 0 ) cout << "\n";
		i++;
		temp = temp->next;
	}
	cout << temp->name << " (" << temp->size << " KB)" << "\t";
}
