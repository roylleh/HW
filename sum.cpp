//Issue during interview: Not using a simpler solution such as the one below.
//Space: O(1)
//Time: O(n)

#include <iostream>

using namespace std;

struct Node
{
	int val;
	Node *next;

	Node(int val)
	{
		this->val = val;
	}
};

Node *sumTwoLists(Node *firstHead, Node *secondHead)
{
	int first = 0;
	int second = 0;

	while (firstHead)
	{
		first = first * 10 + firstHead->val;
		firstHead = firstHead->next;
	}

	while (secondHead)
	{
		second = second * 10 + secondHead->val;
		secondHead = secondHead->next;
	}

	int result = first + second;
	Node *head = new Node(result % 10);
	result /= 10;

	while (result)
	{
		Node *tmp = new Node(result % 10);
		tmp->next = head;
		head = tmp;
		result /= 10;
	}

	return head;
}

int main()
{
	Node *firstHead = new Node(5);
	firstHead->next = new Node(6);
	firstHead->next->next = new Node(3);

	Node *secondHead = new Node(8);
	secondHead->next = new Node(4);
	secondHead->next->next = new Node(2);

	Node *result = sumTwoLists(firstHead, secondHead);

	while (result)
	{
		cout << result->val << " ";
		result = result->next;
	}

	cout << endl;
	return 0;
}