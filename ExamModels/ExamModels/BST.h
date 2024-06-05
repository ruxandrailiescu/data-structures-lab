#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Arrival
{
	char* trainCode;
	char* comingFrom;
	char* arrivalTime;
	unsigned short delay;
	unsigned short noPassengers;
} Arrival;

Arrival* createArrival(const char* trainC, const char* comingF, const char* arrivalT, unsigned short delayM, unsigned short pass)
{
	Arrival* arrival = (Arrival*)malloc(sizeof(Arrival));
	arrival->trainCode = (char*)malloc(strlen(trainC) + 1);
	strcpy(arrival->trainCode, trainC);
	arrival->comingFrom = (char*)malloc(strlen(comingF) + 1);
	strcpy(arrival->comingFrom, comingF);
	arrival->arrivalTime = (char*)malloc(sizeof(arrivalT) + 1);
	strcpy(arrival->arrivalTime, arrivalT);
	arrival->delay = delayM;
	arrival->noPassengers = pass;
	return arrival;
}

void displayArrival(Arrival* arrival)
{
	if (arrival)
	{
		printf("Train code: %s, Coming from: %s, Arrival time: %s, Delay: %d, Passengers: %d\n",
			arrival->trainCode, arrival->comingFrom, arrival->arrivalTime, arrival->delay, arrival->noPassengers);
	}
}

void deleteArrival(Arrival* arrival)
{
	if (arrival)
	{
		free(arrival->trainCode);
		free(arrival->comingFrom);
		free(arrival->arrivalTime);
		free(arrival);
	}
}

typedef struct TreeN
{
	struct TreeN* left;
	Arrival* arrival;
	struct TreeN* right;
} TreeNode;

TreeNode* createNode(Arrival* arrival)
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->arrival = arrival;
	node->left = node->right = NULL;
	return node;
}

void upsert(TreeNode** root, Arrival* arrival)
{
	if (*root == NULL)
	{
		TreeNode* node = createNode(arrival);
		*root = node;
	}
	else
	{
		if (strcmp((*root)->arrival->arrivalTime, arrival->arrivalTime) > 0)
		{
			upsert(&(*root)->left, arrival);
		}
		else if (strcmp((*root)->arrival->arrivalTime, arrival->arrivalTime) < 0)
		{
			upsert(&(*root)->right, arrival);
		}
		else
		{
			printf("Key already exists!");
			(*root)->arrival = arrival;
		}
	}
}

void inorder(TreeNode* root)
{
	if (root)
	{
		inorder(root->right);
		displayArrival(root->arrival);
		inorder(root->left);
	}
}

char* getMax(TreeNode* root)
{
	if (root)
	{
		while (root->right)
		{
			root = root->right;
		}
		printf("\n");
		displayArrival(root->arrival);
		return root->arrival->arrivalTime;
	}
	return NULL;
}

int getDelays(TreeNode* root)
{
	if (root)
	{
		if (root->arrival->delay > 0)
		{
			return 1 + getDelays(root->left) + getDelays(root->right);
		}
		else
		{
			return getDelays(root->left) + getDelays(root->right);
		}
	}
	return 0;
}

int getTotalPassengers(TreeNode* root, const char* src)
{
	if (root)
	{
		if (strcmp(root->arrival->comingFrom, src) == 0)
		{
			return root->arrival->noPassengers + getTotalPassengers(root->left, src) + getTotalPassengers(root->right, src);
		}
		else
		{
			return getTotalPassengers(root->left, src) + getTotalPassengers(root->right, src);
		}
	}
	return 0;
}

Arrival** expand(Arrival** arrivals, int noEl)
{
	Arrival** result = (Arrival**)malloc(sizeof(Arrival*) * (noEl + 1));
	for (int i = 0; i < noEl; i++)
	{
		result[i] = arrivals[i];
	}
	return result;
}

void convertToArray(TreeNode* root, const char* time, Arrival*** arrivalsPath, int* noEl)
{
	if (root)
	{
		if (strcmp(root->arrival->arrivalTime, time) > 0)
		{
			convertToArray(root->left, time, arrivalsPath, noEl);
		}
		else
		{
			if (strcmp(root->arrival->arrivalTime, time) < 0)
			{
				convertToArray(root->right, time, arrivalsPath, noEl);
			}
			else
			{
				*arrivalsPath = (Arrival**)malloc(sizeof(Arrival*) * 1);
				(*arrivalsPath)[(*noEl)++] = root->arrival;
			}
		}
		
		if (strcmp(root->arrival->arrivalTime, time) != 0)
		{
			*arrivalsPath = expand(*arrivalsPath, *noEl);
			(*arrivalsPath)[(*noEl)++] = root->arrival;
		}
	}
}