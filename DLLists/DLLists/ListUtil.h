#pragma once
#include "DataUtil.h"

typedef struct Node
{
	struct Node* prev;
	Student* info;
	struct Node* next;
}ListNode, *PListNode;

ListNode* createNode(Student* stud)
{
	ListNode* node = NULL;
	node = (ListNode*)malloc(sizeof(ListNode));
	node->info = stud;
	node->next = node->prev = NULL;
	return node;
}

void insertTail(ListNode** headList, Student* stud)
{
	ListNode* node = createNode(stud);
	if ((*headList) == NULL)
	{
		(*headList) = node;
	}
	else
	{
		ListNode* tmp = (*headList);
		while (tmp->next)
			tmp = tmp->next;
		// connect the node to the structure
		node->prev = tmp;
		// connect the structure to the node
		tmp->next = node;
	}
}

void insertHead(ListNode** headList, Student* stud)
{
	ListNode* node = createNode(stud);
	if ((*headList) != NULL)
	{
		node->next = (*headList);
		(*headList)->prev = node;
	}
	(*headList) = node;
}

void deleteNode(ListNode* node)
{
	if (node != NULL)
	{
		deleteStudent(node->info);
		free(node);
	}
}

void deleteNodeByKey(ListNode** headList, const char* key)
{
	ListNode* tmp = (*headList);
	while (tmp)
	{
		if (strcmp(tmp->info->name, key) == 0)
		{
			if (tmp->prev != NULL)
			{
				// update next of previous node
				// if node to be deleted is not the head
				tmp->prev->next = tmp->next;
			}
			if (tmp->next != NULL)
			{
				// update prev of next node
				// if node to be deleted is not the tail
				tmp->next->prev = tmp->prev;
			}
			if (tmp == (*headList))
			{
				// update head if deleting the first node
				(*headList) = tmp->next;
			}
			deleteNode(tmp);
			return;
		}
		tmp = tmp->next;
	}
}

void deleteList(ListNode** headList)
{
	while ((*headList) != NULL)
	{
		ListNode* tmp = (*headList);
		(*headList) = tmp->next;
		printStudent(tmp->info);
		deleteNode(tmp);
	}
}

void printList(ListNode* headList)
{
	ListNode* tmp = headList;
	do
	{
		printStudent(tmp->info);
		tmp = tmp->next;
	} while (tmp != NULL);
}