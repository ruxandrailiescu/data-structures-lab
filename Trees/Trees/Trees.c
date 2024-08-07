#define _CRT_SECURE_NO_WARNINGS
#include "TreeUtil.h"

#define LINE_SIZE 256

void main()
{
	TreeNode* root = NULL;
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
			upsert(&root, stud);
			//DisplayTreeStructure(root, 0);
			//printf("-----------------------------------------\n");
		}

		DisplayTreeStructure(root, 0);
		//deleteNodeByKey(&root, 255);
		//DisplayTreeStructure(root, 0);

		int numNodes = 0;
		countNodesGreaterThan(root, 32, &numNodes);
		printf("\nNodes greater than: %d\n", numNodes);
	}
}