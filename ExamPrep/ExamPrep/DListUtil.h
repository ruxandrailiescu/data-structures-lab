#pragma once
#include "DataUtil.h"

typedef struct NodeDLL {
	Student* info;
	struct NodeDLL* next;
	struct NodeDLL* prev;
} Node;

// create node
Node* createNodeDL(Student* info)
{
	Node* node = NULL;
	node = (Node*)malloc(sizeof(Node));
	node->info = info;
	node->prev = node->next = NULL;
	return node;
}

// insert node - head, tail, after node
void insertHeadDL(Node** head, Student* stud)
{
	Node* node = createNodeDL(stud);
	if ((*head) == NULL)
		(*head) = node;
	else
	{
		node->next = (*head);
		(*head)->prev = node;
		(*head) = node;
	}
}

void insertTailDL(Node** head, Student* stud)
{
	Node* node = createNodeDL(stud);
	if ((*head) == NULL)
		(*head) = node;
	else
	{
		Node* tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		node->prev = tmp;
		tmp->next = node;
	}
}

void insertAfterNodeDL(Node** head, Student* stud, unsigned char key)
{
	Node* node = createNodeDL(stud);
	if ((*head) == NULL)
		(*head) = node;
	else
	{
		Node* tmp = *head;
		while (tmp->next)
		{
			if (tmp->info->reference.intRef == key)
			{
				Node* aux = tmp;
				tmp->next = node;
				node->prev = tmp;
				node->next = aux->next->next;
				aux->next->next->prev = node;
				return;
			}
			tmp = tmp->next;
		}
	}
}

// delete node
// delete list
// concatenate list
// create circular list
// merge circular lists
// display circular list