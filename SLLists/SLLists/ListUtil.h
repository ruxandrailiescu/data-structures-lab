#pragma once
#include "DataUtil.h"

typedef struct Node
{
	Student* info;
	struct Node* next;
}ListNode, * PListNode;

ListNode* createNode(Student* stud)
{
	ListNode* node = NULL;
	node = (ListNode*)malloc(sizeof(ListNode));
	node->info = stud;
	node->next = NULL;
	return node;
}

void insertStudent(ListNode** headList, Student* stud)
{
	ListNode* node = createNode(stud);
	// insert at beginning of list
	node->next = (*headList);
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
	} while (tmp != headList);
}

void makeListCircular(ListNode** headList)
{
	if ((*headList) != NULL)
	{
		ListNode* tmp = (*headList);
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = (*headList);
	}
}