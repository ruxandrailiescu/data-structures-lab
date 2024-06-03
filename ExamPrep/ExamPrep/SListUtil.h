#pragma once
#include "DataUtil.h"

typedef struct NodeSLL {
	Student* info;
	struct NodeSLL* next;
} ListNode;

// create node
ListNode* createNodeSL(Student* info)
{
	ListNode* node = NULL;
	node = (ListNode*)malloc(sizeof(ListNode));
	node->info = info;
	node->next = NULL;
	return node;
}

// insert node - head, tail, after node
void insertHeadSL(ListNode** head, Student* stud)
{
	ListNode* node = createNodeSL(stud);
	if ((*head) == NULL)
		(*head) = node;
	else
	{
		node->next = (*head);
		(*head) = node;
	}
}

void insertTailSL(ListNode** head, Student* stud)
{
	ListNode* node = createNodeSL(stud);
	if ((*head) == NULL)
		(*head) = node;
	else
	{
		ListNode* tmp = (*head);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

void insertAfterNodeSL(ListNode** head, Student* stud, unsigned char key)
{
	ListNode* node = createNodeSL(stud);
	if ((*head) == NULL)
		(*head) = node;
	else
	{
		ListNode* tmp = (*head);
		while (tmp->next)
		{
			if (tmp->info->reference.intRef == key)
			{
				ListNode* nxt = tmp->next;
				tmp->next = node;
				node->next = nxt;
				return;
			}
			tmp = tmp->next;
		}
	}
}

// delete node by key
void deleteNodeByKeySL(ListNode** head, char* name)
{
	ListNode* tmp = (*head);
	ListNode* prev = NULL;
	if (*head == NULL)
	{
		return;
	}
	else
	{
		if (strcmp(tmp->info->name, name) == 0)
		{
			(*head) = tmp->next;
			deleteStudent(tmp->info);
			free(tmp);
			return;
		}

		while (tmp->next)
		{
			prev = tmp;
			tmp = tmp->next;
			if (strcmp(tmp->info->name, name) == 0)
			{
				prev->next = tmp->next;
				deleteStudent(tmp->info);
				free(tmp);
				return;
			}
		}
	}
}

// delete list
void deleteListSL(ListNode** head)
{
	while ((*head) != NULL)
	{
		ListNode* tmp = (*head);
		(*head) = tmp->next;
		deleteStudent(tmp->info);
		free(tmp);
	}
}

// concatenate lists
ListNode* concatenateSL(ListNode* list1, ListNode* list2)
{
	if (list1 == NULL)
		return list2;

	if (list2 == NULL)
		return list1;

	ListNode* tmp = list1;
	while (tmp->next)
		tmp = tmp->next;

	tmp->next = list2;

	return list1;
}

// merge sort list
void splitListSL(ListNode* source, ListNode** frontRef, ListNode** backRef)
{
	ListNode* fast;
	ListNode* slow;
	slow = source;
	fast = source->next;

	// fast pointer moves two nodes, slow pointer moves one node
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}

	// split the list into two halves
	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL;
}

ListNode* sortedMergeSL(ListNode* a, ListNode* b)
{
	ListNode* result = NULL;

	// base cases
	if (a == NULL)
		return b;
	if (b == NULL)
		return a;

	// recursive call
	if (a->info->income <= b->info->income)
	{
		result = a;
		result->next = sortedMergeSL(a->next, b);
	}
	else
	{
		result = b;
		result->next = sortedMergeSL(a, b->next);
	}

	return result;
}

void mergeSortSL(ListNode** headRef)
{
	ListNode* head = *headRef;
	ListNode* a;
	ListNode* b;

	// base case: length 0 or 1
	if ((head == NULL) || (head->next == NULL))
		return;

	// split the list into two halves
	splitListSL(head, &a, &b);

	// recursively sort the two halves
	mergeSortSL(&a);
	mergeSortSL(&b);

	// merge the two sorted halves
	*headRef = sortedMergeSL(a, b);
}

// create circular list
ListNode* createCircularSL(ListNode* head)
{
	if (head == NULL)
		return NULL;

	ListNode* tmp = head;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = head;
	
	return head;
}

// merge circular lists
ListNode* mergeCircularListsSL(ListNode* list1, ListNode* list2)
{
	if (list1 == NULL)
		return list2;
	
	if (list2 == NULL)
		return list1;

	ListNode* tail1 = list1;
	while (tail1->next != list1)
	{
		tail1 = tail1->next;
	}

	ListNode* tail2 = list2;
	while (tail2->next != list2)
	{
		tail2 = tail2->next;
	}

	// join the two lists
	tail1->next = list2;
	tail2->next = list1;

	return list1;
}

// display circular list
void displayCircularListSL(ListNode* list)
{
	ListNode* head = list;
	if (head != NULL)
	{
		do
		{
			printStudent(list->info);
			list = list->next;
		} while (list != head);
	}
}