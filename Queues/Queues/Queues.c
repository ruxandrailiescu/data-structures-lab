#include "QueueUtil.h"
#define LINE_SIZE 256

void main()
{
	QueueNode* tailQueue = NULL;
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
			putNode(&tailQueue, stud);
		}
		displayQueue(&tailQueue);
		printf("\n\n");
		Student* stud1 = peekNode(tailQueue);
		printStudent(stud1);
		printf("\n\n");
		stud1 = popNode(&tailQueue);
		printStudent(stud1);
		printf("\n\n");
		stud1 = popNode(&tailQueue);
		printStudent(stud1);
		printf("\n\n");
		displayQueue(&tailQueue);
	}
}