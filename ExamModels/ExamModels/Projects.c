#define LINE_SIZE 256
#include "DLL.h"

void main()
{
	ListNode* head = NULL;
	FILE* pFile = fopen("Data1.txt", "r");
	if (pFile)
	{
		char delimiter[] = ",\n";
		char* token = NULL;
		char buffer[LINE_SIZE], title[LINE_SIZE], benef[LINE_SIZE];
		unsigned int code;
		unsigned char noEx;
		float budget;

		while (fgets(buffer, sizeof(buffer), pFile))
		{
			token = strtok(buffer, delimiter);
			code = atoi(token);
			token = strtok(NULL, delimiter);
			strcpy(title, token);
			token = strtok(NULL, delimiter);
			strcpy(benef, token);
			token = strtok(NULL, delimiter);
			noEx = (char)atoi(token);
			token = strtok(NULL, delimiter);
			budget = atof(token);
			Project* project = createProject(code, title, benef, noEx, budget);
			//displayProject(project);
			insertHeadNode(&head, project);
		}
	}
	//displayList(head);
	//int noProj = 0;
	//getNoProjects(head, 5, &noProj);
	//printf("%d\n", noProj);

	//updateProjects(&head, "Ionescu Mihai", 20);
	//printf("\n\n");
	//sortList(&head);

	PQueue pQueue = { .items = NULL, .currentIndex = 0 };
	enqueue(&pQueue, head, "Ionescu Mihai");
	for (int i = 0; i < pQueue.currentIndex; i++)
	{
		displayProject(pQueue.items[i]);
	}
}