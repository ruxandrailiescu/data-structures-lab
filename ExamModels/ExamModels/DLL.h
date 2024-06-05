#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Project
{
	unsigned int code;
	char* title;
	char* benef;
	unsigned char noEx;
	float budget;
} Project;

typedef struct NodeDLL
{
	struct NodeDLL* prev;
	Project* info;
	struct NodeDLL* next;
} ListNode;

typedef struct PQueue
{
	Project** items;
	int currentIndex;
} PQueue;

Project* createProject(unsigned int code, const char* title, const char* benef, unsigned char noEx, float budget)
{
	Project* project = (Project*)malloc(sizeof(Project));
	project->code = code;
	project->title = (char*)malloc(strlen(title) + 1);
	strcpy(project->title, title);
	project->benef = (char*)malloc(strlen(benef) + 1);
	strcpy(project->benef, benef);
	project->noEx = noEx;
	project->budget = budget;
	return project;
}

void displayProject(Project* project)
{
	if (project)
	{
		printf("Code: %d, Title: %s, Beneficiary: %s, No ex: %d, Budget: %f\n", project->code, project->title,
			project->benef, project->noEx, project->budget);
	}
}

ListNode* createNodeDL(Project* project)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->info = project;
	node->prev = node->next = NULL;
	return node;
}

void insertHeadNode(ListNode** head, Project* project)
{
	ListNode* node = createNodeDL(project);
	
	if (*head)
	{
		node->next = *head;
		(*head)->prev = node;
	}
	*head = node;
}

void displayList(ListNode* head)
{
	while (head)
	{
		displayProject(head->info);
		head = head->next;
	}
}

void getNoProjects(ListNode* head, int noEx, int* noProj)
{
	while (head)
	{
		if (head->info->noEx >= noEx)
		{
			(*noProj)++;
		}
		head = head->next;
	}
}

void displayListBothWays(ListNode* head)
{
	if (head)
	{
		while (head->next)
		{
			displayProject(head->info);
			head = head->next;
		}
		displayProject(head->info);
		printf("----------------Reversed order----------------\n");
		while (head)
		{
			displayProject(head->info);
			head = head->prev;
		}
	}
}

void updateProjects(ListNode** head, const char* benef, float percentage)
{
	if (*head)
	{
		ListNode* current = *head;
		while (current)
		{
			if (strcmp(current->info->benef, benef) == 0)
			{
				current->info->budget = current->info->budget * (1 + percentage / 100);
			}
			current = current->next;
		}
		displayListBothWays(*head);
	}
}

void sortList(ListNode** head)
{
	if (*head)
	{
		int swapped;
		ListNode* current;
		ListNode* lastPtr = NULL;

		do
		{
			swapped = 0;
			current = *head;

			while (current->next != lastPtr)
			{
				if (current->info->budget > current->next->info->budget)
				{
					Project* tmp = current->info;
					current->info = current->next->info;
					current->next->info = tmp;
					swapped = 1;
				}
				current = current->next;
			}
			lastPtr = current;
		} while (swapped);

		displayListBothWays(*head);
	}
}

void reheapUp(Project** items, int currentIndex)
{
	if (currentIndex > 0)
	{
		int parentIndex = (currentIndex - 1) / 2;
		if (items[parentIndex]->code < items[currentIndex]->code)
		{
			Project* aux = items[parentIndex];
			items[parentIndex] = items[currentIndex];
			items[currentIndex] = aux;
			reheapUp(items, parentIndex);
		}
	}
}

Project** expandQ(Project** projects, int noEl)
{
	Project** result = (Project**)malloc(sizeof(Project*) * (noEl + 1));
	for (int i = 0; i < noEl; i++)
	{
		result[i] = projects[i];
	}
	return result;
}

void enqueue(PQueue* pQueue, ListNode* head, const char* benef)
{
	while (head)
	{
		if (strcmp(head->info->benef, benef) == 0)
		{
			(*pQueue).items = expandQ((*pQueue).items, (*pQueue).currentIndex);
			(*pQueue).items[(*pQueue).currentIndex] = head->info;
			if ((*pQueue).currentIndex > 0)
			{
				reheapUp((*pQueue).items, (*pQueue).currentIndex);
			}
			(*pQueue).currentIndex++;
		}
		head = head->next;
	}
}