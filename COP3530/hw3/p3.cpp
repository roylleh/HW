#include <algorithm>
#include <iostream>

using namespace std;

struct node
{
	int data;
	node *leftPtr;
	node *rightPtr;
};

int height( node *temp );

node* makeTree( int post[], int in[], int nodes );
node* okayNowActuallyMakeTree( int post[], int in[], int start, int end, int *index );
void levelOrder( node *temp, int level );

int main()
{
	int j, nodes;
	cin >> nodes;
	
	int post[ nodes ];
	int in[ nodes ];
	cout << "\n";
	
	for( int i = 0; i < 2; i++ )
	{
		for( int j = 0; j < nodes; j++ )
		{
			if( i == 0 ) cin >> post[j];
			else cin >> in[j];
		}
	}
	
	node *root = makeTree( post, in, nodes );
	cout << "\n";
	
	j = height( root );
	
	for( int i = 1; i <= j; i++ )
	{
		levelOrder( root, i );
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

node* makeTree( int post[], int in[], int nodes )
{
	int index = nodes - 1;
	return okayNowActuallyMakeTree( post, in, 0, nodes - 1, &index );
}

node* okayNowActuallyMakeTree( int post[], int in[], int start, int end, int *index )
{
	if( start > end ) return NULL;
	
	node *temp = new node;
	temp->data = post[ *index ];
	temp->leftPtr = NULL;
	temp->rightPtr = NULL;
	(*index)--;
	
	if( start == end ) return temp;
	
	int i;
	for( i = start; i <= end; i++ )
	{
		if( in[i] == temp->data ) break;
	}
	
	temp->rightPtr = okayNowActuallyMakeTree( post, in, i + 1, end, index );
	temp->leftPtr = okayNowActuallyMakeTree( post, in, start, i - 1, index );
	
	return temp;
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
