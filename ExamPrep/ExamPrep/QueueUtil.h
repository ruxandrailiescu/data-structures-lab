#pragma once
#include "DataUtil.h"

// CIRCULAR QUEUE

typedef struct NodeQ
{
	Student* info;
	struct NodeQ* next;
} QueueNode;

QueueNode* createNodeQueue(Student* info)
{
	QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
	node->info = info;
	node->next = NULL;
	return node;
}

void putNodeQueue(QueueNode** tailQueue, Student* stud)
{
	QueueNode* node = createNodeQueue(stud);

	if (*tailQueue == NULL)
		node->next = node;
	else
	{
		node->next = (*tailQueue)->next;
		(*tailQueue)->next = node;
	}

	(*tailQueue) = node;
}

Student* peekNodeQueue(QueueNode* tailQueue)
{
	if (tailQueue == NULL)
		return NULL;

	return tailQueue->next->info;
}

//Student* peekNode(QueueNode* tailQueue)
//{
//	Student* result = NULL;
//	if (tailQueue != NULL)
//	{
//		result = tailQueue->next->info;
//	}
//	return result;
//}

Student* getNodeQueue(QueueNode** tailQueue)
{
	if (*tailQueue == NULL)
		return NULL;

	QueueNode* head = (*tailQueue)->next;
	Student* result = head->info;

	if (head == *tailQueue)
	{
		// only one element in the queue
		free(head);
		*tailQueue = NULL;
	}
	else
	{
		(*tailQueue)->next = head->next;
		free(head);
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

void displayQueue(QueueNode* tailQueue)
{
	if (tailQueue == NULL)
		return;

	QueueNode* current = tailQueue->next;
	do
	{
		printStudent(current->info);
		current = current->next;
	} while (current != tailQueue->next);
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