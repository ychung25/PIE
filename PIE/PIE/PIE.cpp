// PIE.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DataStructures.h"

struct Node
{
	int data;
	Node* next;
};

void SelectionSort(int data[], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (data[j] < data[i])
			{
				int temp = data[i];
				data[i] = data[j];
				data[j] = temp;
			}
		}
	}
}

void InsertionSort(int data[], int len)
{
	for (int i = 1; i < len; i++)
	{
		int temp = data[i];
		int j = i - 1;
		while(j >= 0)
		{
			if (data[j] > temp)
				data[j + 1] = data[j];
			else
				break;

			j--;
		}
		data[j + 1] = temp;
	}
}

void QuickSort(int data[], int start, int end)
{
	if (start >= end)
		return;

	int p = (start + end) / 2;
	int temp = data[p];
	int i = start;
	int j = start;
	while (i <= end)
	{
		if (data[j] < temp)
			j++;
		if ((data[i] < temp) && (j < i))
		{
			if (j == p)
			{
				p = i;
			}

			int cache = data[i];
			data[i] = data[j];
			data[j] = cache;
		}
		i++;
	}
	int cache = data[j];
	data[j] = data[p];
	data[p] = cache;

	QuickSort(data, start, j - 1);
	QuickSort(data, j + 1, end);
}

void Merge(int data[], int start, int end)
{
	int size = (end - start) + 1;
	int* temp = new int[size]();
	int i = 0;

	int mid = (start + end) / 2;
	int head1 = start;
	int head2 = mid + 1;
	
	while (head1 <= mid && head2 <= end)
	{
		if (data[head1] < data[head2])
			temp[i++] = data[head1++];
		else
			temp[i++] = data[head2++];
	}

	while (head1 <= mid)
	{
		temp[i++] = data[head1++];
	}
	while (head2 <= end)
	{
		temp[i++] = data[head2++];
	}

	i = 0;
	for (int j = start; j <= end; j++)
	{
		data[j] = temp[i++];
	}
}

void MergeSort(int data[], int start, int end)
{
	if (start == end)
		return;
	int mid = (start + end) / 2;
	MergeSort(data, start, mid);
	MergeSort(data, mid + 1, end);
	Merge(data, start, end);
}

Node* FindMidNode(Node* n)
{
	Node* fast = n;
	Node* slow = n;
	Node* prev = n;;
	while (fast)
	{
		fast = fast->next;
		if (!fast)
			break;
		fast = fast->next;

		prev = slow;
		slow = slow->next;
	}

	return prev;
}

Node* MergeLL(Node* l, Node* r)
{
	if (!r)
		return l;
	if (!l)
		return r;

	Node* head = nullptr;
	Node* current = nullptr;
	while (l && r)
	{
		if (l->data < r->data)
		{
			if (current)
				current->next = l;
			current = l;
			l = l->next;
		}
		else
		{
			if (current)
				current->next = r;
			current = r;
			r = r->next;
		}
		if (!head)
			head = current;
	}

	if (l)
		current->next = l;
	if (r)
		current->next = r;
	
	return head;
}

Node* MergeSortLL(Node* n)
{
	if (!n || !n->next)
		return n;

	Node* mid = FindMidNode(n);
	Node* temp = mid->next;
	mid->next = nullptr;

	Node* l = MergeSortLL(n);
	Node* r = MergeSortLL(temp);
	return MergeLL(l, r);
}


int main()
{
	Node* n1 = new Node();
	n1->data = 1;
	n1->next = nullptr;
	Node* n2 = new Node();
	n2->data = 2;
	n2->next = nullptr;
	Node* n3 = new Node();
	n3->data = 3;
	n3->next = nullptr;
	Node* n4 = new Node();
	n4->data = 4;
	n4->next = nullptr;
	Node* n5 = new Node();
	n5->data = 5;
	n5->next = nullptr;

	n2->next = n1;
	n1->next = n3;
	n3->next = n5;
	n5->next = n4;

	Node* result = MergeSortLL(n2);

	return 0;
}

