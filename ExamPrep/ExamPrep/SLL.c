#define _CRT_SECURE_NO_WARNINGS
#include "SListUtil.h"

#define LINE_SIZE 256

void SLL()
{
	ListNode* head = NULL;
	ListNode* head2 = NULL;
	FILE* pFile = fopen("Data.txt", "r");
	if (pFile)
	{
		char delimiter[] = ",";
		char* token = NULL;
		float income; int index = 0;
		unsigned short reference;
		char buffer[LINE_SIZE], name[LINE_SIZE];
		while (fgets(buffer, sizeof(buffer), pFile))
		{
			token = strtok(buffer, delimiter);
			strcpy(name, token);
			token = strtok(NULL, delimiter);
			income = atof(token);
			token = strtok(NULL, delimiter);
			reference = atoi(token);
			Student* stud = createStudent(name, income, reference);
			insertHeadSL(&head, stud);
			insertHeadSL(&head2, stud);
		}
	}

	Student* stud2 = createStudent("Girica Cristiana", 10000, 23);

	insertAfterNodeSL(&head, stud2, 255);
	//deleteNodeByKeySL(&head, "Albu Cristina");
	//deleteListSL(&head);
	//head = concatenateSL(head, head2);

	mergeSortSL(&head);
	while (head)
	{
		printStudent(head->info);
		head = head->next;
	}


	head = createCircularSL(head);
	head2 = createCircularSL(head2);
	head = mergeCircularListsSL(head, head2);
	displayCircularListSL(head);
}