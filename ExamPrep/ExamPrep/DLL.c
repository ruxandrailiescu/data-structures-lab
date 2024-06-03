#define _CRT_SECURE_NO_WARNINGS
#include "DListUtil.h"

#define LINE_SIZE 256

void main()
{
	Node* head = NULL;
	Node* head2 = NULL;
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
			insertTailDL(&head, stud);
			insertTailDL(&head2, stud);
		}
	}

	Student* stud1 = createStudent("Ruxandra Iliescu", 5000, 23);
	insertAfterNodeDL(&head, stud1, 78);
	deleteNodeByKeyDL(&head, 23);
	//deleteListDL(&head);

	//while (head)
	//{
	//	printStudent(head->info);
	//	head = head->next;
	//}

	head = createCircularDL(head);
	head2 = createCircularDL(head2);
	head = mergeCircularListsDL(head, head2);
	displayListBothWaysCircular(head);
}