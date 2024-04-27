#include "main.h"
#include <ctype.h>

// Leetcode #682

// Implementation using singly-linked lists

typedef struct NodeS
{
	int value;
	struct NodeS* next;
}StackNode;

StackNode* createNode(int value)
{
	StackNode* node = (StackNode*)malloc(sizeof(StackNode));
	node->value = value;
	node->next = NULL;
	return node;
}

void pushNode(StackNode** stack, int value)
{
	StackNode* node = createNode(value);
	if (*stack != NULL)
	{
		node->next = *stack;
	}
	*stack = node;
}

int peekNode(StackNode* stack)
{
	if (stack != NULL)
	{
		int value = stack->value;
		return value;
	}
	return 0;
}

int popNode(StackNode** stack)
{
	if ((*stack) != NULL)
	{
		int value = (*stack)->value;
		StackNode* tmp = (*stack);
		(*stack) = tmp->next;
		free(tmp);
		return value;
	}
	return 0;
}

int calPoints(char** operations, int operationsSize)
{
	if (operations == NULL || operationsSize == 0)
		return 0;
	
	int points = 0;
	StackNode* stack = NULL;

	for (int i = 0; i < operationsSize; i++)
	{
		if (strcmp(operations[i], "C") == 0)
		{
			int value = popNode(&stack);
			printf("\nPopped value: %d", value);
		}
		else if (strcmp(operations[i], "D") == 0)
		{
			int value = peekNode(stack);
			pushNode(&stack, value * 2);
		}
		else if (strcmp(operations[i], "+") == 0)
		{
			int value1 = popNode(&stack);
			int value2 = peekNode(stack);
			pushNode(&stack, value1);
			pushNode(&stack, value1 + value2);
		}
		else
		{
			int value = atoi(operations[i]);
			pushNode(&stack, value);
		}
	}

	while (stack)
	{
		points += popNode(&stack);
	}
	return points;
}

void main()
{
	char** ops = (char**)malloc(sizeof(char*) * 5);
	for (int i = 0; i < 5; i++)
	{
		ops[i] = (char*)malloc(sizeof(char));
		printf("\nEnter operation %d: ", i + 1);
		scanf("%s", ops[i]);
	}
	int points = calPoints(ops, 5);
	printf("\nPoints: %d", points);
}