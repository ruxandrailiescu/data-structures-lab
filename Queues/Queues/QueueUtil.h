#pragma once
#include "DataUtil.h"

typedef struct NodeQ
{
	Student* info;
	struct NodeQ* next;
}QueueNode, *PQueueNode;

QueueNode* createQueueNode(Student* info)
{
	QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
	node->info = info;
	node->next = NULL;
	return node;
}

void putNode(QueueNode** tail, Student* stud)
{
	QueueNode* node = createQueueNode(stud);
	if ((*tail) != NULL)
	{
		node->next = (*tail);
	}
	(*tail) = node;
}

Student* peekNode(QueueNode* tail)
{
	Student* result = NULL;
	// iterate from tail to head
	// until head is reached
	if (tail != NULL)
	{
		while (tail->next != NULL)
		{
			tail = tail->next;
		}
		result = tail->info;
	}
	return result;
}

Student* popNode(QueueNode** tail)
{
	Student* result = NULL;
	if ((*tail) != NULL)
	{
		QueueNode* tmp = (*tail);
		while (tmp->next->next != NULL)
		{
			tmp = tmp->next;
		}
		// tmp->next->next == NULL
		// set next pointer of tmp == NULL to remove head
		result = tmp->next->info;
		tmp->next = NULL;
	}
	return result;
}

//Student* getNode(QueueNode** tailQueue)
//{
//	Student* result = NULL;
//	if (*tailQueue != NULL)
//	{
//		result = (*tailQueue)->next->info;
//		if ((*tailQueue)->next == (*tailQueue))
//		{
//			free(*tailQueue);
//			(*tailQueue) = NULL;
//		}
//		else
//		{
//			QueueNode* head = (*tailQueue)->next;
//			(*tailQueue)->next = head->next;
//			free(head);
//		}
//	}
//	return result;
//}

void displayQueue(QueueNode** tail)
{
	Student* info = peekNode(*tail);
	Student* tmp = NULL;
	while (tmp != info)
	{
		tmp = popNode(tail);
		putNode(tail, tmp);
		printStudent(tmp);
		tmp = peekNode(*tail);
	}
}

//void displayQueue(QueueNode** tailQueue)
//{
//	Student* info = peekNode(*tailQueue);
//	Student* tmp = NULL;
//	while (tmp != info)
//	{
//		tmp = getNode(tailQueue);
//		putNode(tailQueue, tmp);
//		printStudent(tmp);
//		tmp = peekNode(*tailQueue);
//	}
//}