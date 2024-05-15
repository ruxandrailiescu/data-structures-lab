#define _CRT_SECURE_NO_WARNINGS
//#include "ListUtil.h"
#include "PQueueUtil.h"

#define LINE_SIZE 256

void main()
{
//	ListNode* list = NULL;
	PriorityQueue pQueue = { .items = NULL, .currentIndex = 0, .size = 0 };
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
			enqueue(&pQueue, stud);
//			list = insertHead_SLNode(list, stud);
		}

//		ListNode* mirroredDL = convert(list);
//		displayListBothWaysCircular(mirroredDL);

		changePrio(&pQueue, 0, 2000);

		Student* info = deque(&pQueue);
		printStudent(info);
	}
}