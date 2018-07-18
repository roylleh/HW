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

int height( node *temp );
void find( node *temp, int i );
void levelOrder( node *temp, int level );

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
	cout << "\n";
	
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
	cout << "\n";
	
	curr = root;
	j = height( curr );
	
	for( int i = 1; i <= j; i++ )
	{
		levelOrder( curr, i );
	}
	cout << "\n";
}

int height( node *temp )
{
	if( temp != NULL )
	{
		int lHeight = height( temp->leftPtr );
		int rHeight = height( temp->rightPtr );
		
		if( lHeight > rHeight ) return lHeight + 1;
		else return rHeight + 1;
	}
	else return 0;
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

void levelOrder( node *temp, int level )
{
	if( temp == NULL ) return;
	if( level == 1 ) cout << temp->data << " ";
	else if( level > 1 )
	{
		levelOrder( temp->leftPtr, level - 1 );
		levelOrder( temp->rightPtr, level - 1 );
	}
}