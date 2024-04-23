#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Model Test SDD 2022-2023
// Requirements

/*
	You are given 2 simple linked lists.
	1. Make them circular;
	2. Make a print function to show both of them;
	3. Merge the two lists so that they are sorted by internal reference.
*/

typedef union Reference
{
	unsigned char intRef;
	unsigned short extRef;
}RefInfo;

typedef struct Student
{
	char* name;
	float income;
	RefInfo reference;
}StudentInfo;

typedef struct Node
{
	StudentInfo* info;
	struct Node* next;
}ListNode;

StudentInfo* createStudentInfo(const char*, double, unsigned short);
void* deleteStudentInfo(StudentInfo*);
void displayStudent(StudentInfo*);
ListNode* createNode(StudentInfo*);
void insertNode(ListNode**, ListNode*);
void loadListFromFile(ListNode**, FILE*);
void printCircularList(ListNode*);
ListNode* mergeList(ListNode*, ListNode*);
ListNode* testMerge(ListNode*, ListNode*);


void main()
{
	
}

ListNode* mergeList(ListNode* list1, ListNode* list2)
{
	ListNode* aux = list1;
	while (aux->next != list1)
	{
		aux = aux->next;
	}
	aux->next = list2;
	aux = list2;
	while (aux->next != list2)
	{
		aux = aux->next;
	}
	aux->next = list1;
	aux = list1;

	while (aux->next != list1)
	{
		ListNode* aux2 = aux->next;
		while (aux2 != list1)
		{
			if (aux->info->reference.intRef > aux2->info->reference.intRef)
			{
				StudentInfo* auxStud = aux->info;
				aux->info = aux2->info;
				aux2->info = auxStud;
			}
			aux2 = aux2->next;
		}
		aux = aux->next;
	}

	return list1;
}