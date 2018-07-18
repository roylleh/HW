#include <iostream>

using namespace std;

struct node
{
	node *next;
	int data;
};

int main()
{
	node *head = new node;
	node *temp = new node;
	node *curr = head;
	
	int length, lists, step, j;
	cin >> length;
	
	//First List
	for( int i = 0; i < length; i++ )
	{
		cin >> curr->data;
		curr->next = new node;
		curr = curr->next;
	}
	curr->next = NULL;
	cin >> lists;
	cout << "\n";
	
	//Next Lists
	for( int i = 0; i < lists; i++ )
	{
		cin >> step;
		cin >> length;
		curr = head;
		j = 0;
		
		while( curr->next != NULL )
		{
			if( length > 0 && (j + 1) % step == 0 )
			{
				temp->next = curr->next;
				curr->next = new node;
				cin >> curr->next->data;
				curr->next->next = temp->next;
				curr = curr->next;
				length--;
			}
			curr = curr->next;
			j++;
		}
		cout << "\n";
	}
	curr = head;
	
	//Print Finalized List
	while( curr->next != NULL )
	{
		cout << curr->data << " ";
		curr = curr->next;
	}
	cout << "\n";
}
