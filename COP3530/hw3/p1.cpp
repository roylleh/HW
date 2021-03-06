#include <algorithm>
#include <iostream>

using namespace std;

struct node
{
	int num;
	int data;
	int left;
	int right;
	node *leftPtr;
	node *rightPtr;
};

bool nodeCompare( node lhs, node rhs )
{
	return lhs.data < rhs.data;
}

node *root = new node;
node *curr = root;

void find( node *temp, int i );
void preOrder( node *temp );
void inOrder( node *temp );
void postOrder( node *temp );

int main()
{
	int j;
	int left;
	int right;
	int nodes;
	cin >> nodes;
	cout << "\n";
	
	node array[nodes];
	
	for( int i = 0; i < nodes; i++ )
	{
		array[i].num = i;
		cin >> array[i].data;
		cin >> array[i].left;
		cin >> array[i].right;
	}
	sort( array, array + nodes, nodeCompare );
	
	for( int i = 0; i < nodes; i++ )
	{
		curr = root;
		if( i == 0 ) curr->num = 0;
		else find( curr, i );
		curr->data = array[i].data;
		
		left = array[i].left;
		for( j = 0; j < nodes; j++ )
		{
			if( array[j].num == left )
			{
				left = j;
				break;
			}
		}
		if( left > 0 )
		{
			curr->leftPtr = new node;
			curr->leftPtr->num = left;
		}
		
		right = array[i].right;
		for( j = 0; j < nodes; j++ )
		{
			if( array[j].num == right )
			{
				right = j;
				break;
			}
		}
		if( right > 0 )
		{
			curr->rightPtr = new node;
			curr->rightPtr->num = right;
		}
	}
	
	curr = root;
	cout << "\n";
	
	preOrder(curr);
	cout << "\n";
	
	inOrder(curr);
	cout << "\n";
	
	postOrder(curr);
	cout << "\n";
}

void find( node *temp, int i )
{
	if( temp != NULL )
	{
		if( temp->num != i ) find( temp->leftPtr, i );
		if( temp->num != i ) find( temp->rightPtr, i );
		if( temp->num == i )
		{
			curr = temp;
			return;
		}
	}
}

void preOrder( node *temp )
{
	if( temp != NULL )
	{
		cout << temp->data << " ";
		preOrder( temp->leftPtr );
		preOrder( temp->rightPtr );
	}
}

void inOrder( node *temp )
{
	if( temp != NULL )
	{
		inOrder( temp->leftPtr );
		cout << temp->data << " ";
		inOrder( temp->rightPtr );
	}
}

void postOrder( node *temp )
{
	if( temp != NULL )
	{
		postOrder( temp->leftPtr );
		postOrder( temp->rightPtr );
		cout << temp->data << " ";
	}
}
