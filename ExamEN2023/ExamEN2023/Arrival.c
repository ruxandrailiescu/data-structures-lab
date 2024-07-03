#define _CRT_SECURE_NO_WARNINGS
#define LINE_SIZE 256
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// IF YOU HAVE TIME DURING THE EXAM, IMPLEMENT FUNCTIONS TO FREE
// HEAP ALLOCATED MEMORY SPACE (e.g., deleteArrival, etc.)


// 1.
typedef struct Arrival
{
	char* trainCode;
	char* comingFrom;
	char* arrivalTime;
	unsigned short delay;
	unsigned short noPassengers;
} Arrival;


Arrival* createArrival(const char* trainCode, const char* comingFrom, const char* arrivalTime,
	unsigned short delay, unsigned short noPass)
{
	Arrival* arrival = NULL;

	if (trainCode && comingFrom && arrivalTime)
	{
		arrival = (Arrival*)malloc(sizeof(Arrival));
		arrival->trainCode = (char*)malloc(strlen(trainCode) + 1);
		strcpy(arrival->trainCode, trainCode);
		arrival->comingFrom = (char*)malloc(strlen(comingFrom) + 1);
		strcpy(arrival->comingFrom, comingFrom);
		arrival->arrivalTime = (char*)malloc(strlen(arrivalTime) + 1);
		strcpy(arrival->arrivalTime, arrivalTime);
		arrival->delay = delay;
		arrival->noPassengers = noPass;
	}

	return arrival;
}

void displayArrival(Arrival* arrival)
{
	if (arrival)
	{
		printf("Train code: %s, Coming from: %s, Arrival time: %s, Delay: %d, No passengers: %d\n",
			arrival->trainCode, arrival->comingFrom, arrival->arrivalTime, arrival->delay, arrival->noPassengers);
	}
}


typedef struct TreeN
{
	struct TreeN* left;
	Arrival* info;
	struct TreeN* right;
} TreeNode;


TreeNode* createTreeNode(Arrival* arrival)
{
	TreeNode* node = NULL;

	if (arrival)
	{
		node = (TreeNode*)malloc(sizeof(TreeNode));
		node->info = arrival;
		node->left = node->right = NULL;
	}

	return node;
}

void upsert(TreeNode** root, Arrival* arrival)
{
	if (*root == NULL)
	{
		TreeNode* node = createTreeNode(arrival);
		*root = node;
	}
	else
	{
		if (strcmp((*root)->info->arrivalTime, arrival->arrivalTime) > 0)
		{
			upsert(&(*root)->left, arrival);
		}
		else if (strcmp((*root)->info->arrivalTime, arrival->arrivalTime) < 0)
		{
			upsert(&(*root)->right, arrival);
		}
		else
		{
			printf("Key already exists, updating it!\n");
			(*root)->info = arrival;
		}
	}
}

void displayTree(TreeNode* root, int level)
{
	if (root != NULL)
	{
		for (int i = 0; i < level; i++)
		{
			printf("\t");
		}
		printf("%s: %s\n", root->info->trainCode, root->info->arrivalTime);

		level++;
		displayTree(root->left, level);
		displayTree(root->right, level);
	}
	else
	{
		for (int i = 0; i < level; i++)
		{
			printf("\t");
		}
		printf("NULL\n");
	}
}

// 2.
void inorder(TreeNode* root)
{
	if (root)
	{
		inorder(root->right);
		displayArrival(root->info);
		inorder(root->left);
	}
}

// 3.
Arrival* getMax(TreeNode* root)
{
	if (root)
	{
		while (root->right)
			root = root->right;

		return root->info;
	}
	return NULL;
}

// 4.
void getArrivalsWithDelay(TreeNode* root, int* count)
{
	if (root == NULL)
	{
		return;
	}

	if (root->info->delay > 0)
	{
		(*count)++;
	}

	getArrivalsWithDelay(root->left, count);
	getArrivalsWithDelay(root->right, count);
}

// 5.
void getTotalNoPassengers(TreeNode* root, int* noPass, const char* comingFrom)
{
	if (root == NULL)
	{
		return;
	}

	if (strcmp(root->info->comingFrom, comingFrom) == 0)
	{
		(*noPass) += root->info->noPassengers;
	}

	getTotalNoPassengers(root->left, noPass, comingFrom);
	getTotalNoPassengers(root->right, noPass, comingFrom);
}

// 6.
Arrival** expand(Arrival** arrivals, int noEl)
{
	Arrival** result = (Arrival**)malloc(sizeof(Arrival*) * (noEl + 1));	// array of pointers
																			// the array does not share 
																			// memory space with the BST implementation
	for (int i = 0; i < noEl; i++)
		result[i] = arrivals[i];
	return result;
}

void convertToArray(TreeNode* root, const char* arrivalTime, Arrival*** arrivalsPath, int* noEl)
{
	if (root)
	{
		if (strcmp(root->info->arrivalTime, arrivalTime) > 0)
		{
			convertToArray(root->left, arrivalTime, arrivalsPath, noEl);
		}
		else
		{
			if (strcmp(root->info->arrivalTime, arrivalTime) < 0)
			{
				convertToArray(root->right, arrivalTime, arrivalsPath, noEl);
			}
			else
			{
				// we found the node
				*arrivalsPath = (Arrival**)malloc(sizeof(Arrival*) * 1);
				(*arrivalsPath)[(*noEl)++] = root->info;
			}
		}

		// process all nodes on the path until the one we're looking for is found
		if (strcmp(root->info->arrivalTime, arrivalTime) != 0)
		{
			*arrivalsPath = expand(*arrivalsPath, *noEl);
			(*arrivalsPath)[(*noEl)++] = root->info;
		}
	}
}

void main()
{
	TreeNode* root = NULL;

	FILE* pFile = fopen("DataArrival.txt", "r");
	if (pFile)
	{
		char delimiter[] = ",";
		char* token = NULL;
		char buffer[LINE_SIZE], trainCode[LINE_SIZE], comingFrom[LINE_SIZE],
			arrivalTime[LINE_SIZE];
		unsigned short delay, noPass;

		while (fgets(buffer, sizeof(buffer), pFile))
		{
			token = strtok(buffer, delimiter);
			strcpy(trainCode, token);
			token = strtok(NULL, delimiter);
			strcpy(comingFrom, token);
			token = strtok(NULL, delimiter);
			strcpy(arrivalTime, token);
			token = strtok(NULL, delimiter);
			delay = atoi(token);
			token = strtok(NULL, delimiter);
			noPass = atoi(token);

			Arrival* arrival = createArrival(trainCode, comingFrom, arrivalTime, delay, noPass);
			//displayArrival(arrival);
			upsert(&root, arrival);
		}
		fclose(pFile);

		displayTree(root, 0);
		
		// 2.
		printf("\n-----------------------------------------\n");
		inorder(root);

		// 3.
		printf("\n-----------------------------------------\n");
		Arrival* lastArrival = getMax(root);
		displayArrival(lastArrival);

		// 4.
		printf("\n-----------------------------------------\n");
		int count = 0;
		getArrivalsWithDelay(root, &count);
		printf("No of arrivals with delays: %d\n", count);

		// 5.
		printf("\n-----------------------------------------\n");
		int countPass = 0;
		getTotalNoPassengers(root, &countPass, "Constanta");
		printf("Total no of passengers: %d\n", countPass);

		// 6.
		printf("\n-----------------------------------------\n");
		int noEl = 0;
		Arrival** arrivalsPath = NULL;
		convertToArray(root, "22:06", &arrivalsPath, &noEl);
		for (int i = 0; i < noEl; i++)
		{
			displayArrival(arrivalsPath[i]);
		}
	}
}