/*
 * @Programmer: Mohammad Qureshi
 * @Project: Programming Assignment #2
 * @Objective: Simulate OS memory management using linked lists.
 */

int procChoice();

class Node
{
	public:
		int num;
		char *name;
		int size;
		Node *next;
		
		Node( int num, char *name, int size );
};

class LinkedList
{
	public:
		Node *head;
		
		LinkedList();
		void insert( int num, char *name, int size );
		void addProgram();
		int findHole( char *algo, int reqPages );
		void endProgram();
		void checkFrag();
		void print();
};
