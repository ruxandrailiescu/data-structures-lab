#include "main.h"

// Leetcode #682

// Implementation using singly-linked lists

typedef struct NodeS
{
	char* info;
	struct NodeS* next;
} StackNode;

StackNode* createNode(char* info)
{	
	if (info == NULL)
		return NULL;
	// allocate memory
	StackNode* node = (StackNode*)malloc(sizeof(StackNode));
	// init node
	node->info = (char*)malloc(strlen(info));
	strcpy(node->info, info);
	node->next = NULL;
	return node;
}

StackNode* pushNode(StackNode* stack, char* info)
{
	StackNode* node = createNode(info);
	node->next = stack;
	return node;
}

char* peekNode(StackNode* stack)
{
	char* info = NULL;
	if (stack != NULL)
	{
		info = (char*)malloc(strlen(stack->info));
		strcpy(info, stack->info);
	}
	return info;
}

char* popNode(StackNode** stack)
{
	char* info = NULL;
	if ((*stack) != NULL)
	{
		info = (char*)malloc(strlen((*stack)->info));
		strcpy(info, (*stack)->info);
		StackNode* tmp = (*stack);
		(*stack) = tmp->next;
		free(tmp);
	}
	return info;
}

int calPoints(char** operations, int operationsSize)
{

}

void main()
{

}