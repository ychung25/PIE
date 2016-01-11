// PIE.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DataStructures.h"

struct Node
{
	int data;
	Node* left;
	Node* right;
};

Node* CreateNode(int data)
{
	Node* n = new Node();
	n->data = data;
	n->left = 0;
	n->right = 0;
	return n;
}

void SetChildren(Node* n, Node* l, Node* r)
{
	n->left = l;
	n->right = r;
}

int Height(Node* n, int i)
{
	if (!n)
		return i;

	int l = Height(n->left, i + 1);
	int r = Height(n->right, i + 1);
	if (l > r)
		return l;
	return r;
}

// Doing it recursive
void PrintPreOrder(Node* n)
{
	DataStructures::Stack<Node*> s;
	while (1)
	{
		if (n)
		{
			s.Push(n);
			printf("%d\n", n->data);
			n = n->left;
		}
		else
		{
			if (s.IsEmpty())
				break;
			n = s.Pop();
			n = n->right;
		}
	}
}

int LCA(Node* n, int a, int b)
{
	if (n->data >= a && n->data <= b)
		return n->data;
	if (b < n->data)
		return LCA(n->left, a, b);
	else
		return LCA(n->right, a, b);
}

int main()
{
	Node* n10 = CreateNode(10);
	Node* n5 = CreateNode(5);
	Node* n15 = CreateNode(15);
	Node* n2 = CreateNode(2);
	Node* n7 = CreateNode(7);
	Node* n13 = CreateNode(13);
	Node* n1 = CreateNode(1);

	SetChildren(n10, n5, n15);
	SetChildren(n5, n2, n7);
	SetChildren(n15, n13, nullptr);
	SetChildren(n2, n1, nullptr);

	int lca = LCA(n10, 5, 13);
	lca = LCA(n10, 13, 15);
	lca = LCA(n10, 2, 7);
	lca = LCA(n10, 1, 7);

	return 0;
}

