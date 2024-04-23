#include "ListUtil.h"
#define LINE_SIZE 256

void main()
{
	ListNode* headList = NULL;
	FILE* pFile = fopen("Data.txt", "r");
	if (pFile)
	{
		char delimiter[] = ",";
		char* token = NULL;
		float income; unsigned short reference;
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
			printStudent(stud);
			insertStudent(&headList, stud);
		}
		printf("\n\n");
		makeListCircular(&headList);
		printList(headList);
		
		if (isCircular(headList)) {
			printf("\n\nIs circular");
		}
		else {
			printf("\n\nIs NOT circular");
		}
	}
}