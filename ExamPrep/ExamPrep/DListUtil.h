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
		while (tmp)
		{
			if (tmp->info->reference.intRef == key)
			{
				Node* nextNode = tmp->next;
				tmp->next = node;
				node->prev = tmp;
				node->next = nextNode;
				if (nextNode)
					nextNode->prev = node;
				return;
			}
			tmp = tmp->next;
		}
	}
}

// delete node
void deleteNodeByKeyDL(Node** head, unsigned char key)
{
	if ((*head) == NULL)
		return;
	
	Node* tmp = *head;

	if (tmp->info->reference.intRef == key)
	{
		*head = tmp->next;
		if (*head)
			(*head)->prev = NULL;
		deleteStudent(tmp->info);
		free(tmp);
		return;
	}

	while (tmp)
	{
		if (tmp->info->reference.intRef == key)
		{
			Node* prev = tmp->prev;
			Node* next = tmp->next;

			if (prev)
				prev->next = next;

			if (next)
				next->prev = prev;

			deleteStudent(tmp->info);
			free(tmp);
			return;
		}
		tmp = tmp->next;
	}
}

// delete list
void deleteListDL(Node** head)
{
	while (*head)
	{
		Node* tmp = *head;
		(*head) = tmp->next;
		if(*head)
			(*head)->prev = NULL;
		deleteStudent(tmp->info);
		free(tmp);
	}
}

// create circular list
Node* createCircularDL(Node* head)
{
	if (head == NULL)
		return NULL;

	Node* tmp = head;
	while (tmp->next)
		tmp = tmp->next;

	tmp->next = head;
	head->prev = tmp;

	return head;
}

// merge circular lists
Node* mergeCircularListsDL(Node* list1, Node* list2)
{
	if (list1 == NULL)
		return list2;

	if (list2 == NULL)
		return list1;

	Node* tail1 = list1;
	while (tail1->next != list1)
		tail1 = tail1->next;

	Node* tail2 = list2;
	while (tail2->next != list2)
		tail2 = tail2->next;

	tail1->next = list2;
	list2->prev = tail1;

	tail2->next = list1;
	list1->prev = tail2;

	return list1;
}

// display circular list
void displayListBothWaysCircular(Node* head)
{
	Node* current = head;
	if (current != NULL)
	{
		do
		{
			printStudent(current->info);
			current = current->next;
		} while (current != head);

		Node* tail = head->prev;
		printf("--------Reverse order-----------\n");
		do
		{
			printStudent(tail->info);
			tail = tail->prev;
		} while (tail != head);
		printStudent(tail->info);
	}
}