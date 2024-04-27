#pragma once
#include "DataUtil.h"

typedef struct NodeS
{
	Student* info;
	struct NodeS* next;
}StackNode, *PStackNode;

StackNode* createStackNode(Student* info)
{
	// allocate memory
	StackNode* node = (StackNode*)malloc(sizeof(StackNode));
	// init node
	node->info = info;
	node->next = NULL;
	return node;
}

StackNode* pushNode(StackNode** stack, Student* info)
{
	StackNode* node = createStackNode(info);
	if (*stack != NULL)
	{
		node->next = *stack;
	}
	*stack = node;
	return node;
}

Student* peekNode(StackNode* stack)
{
	Student* info = NULL;
	if (stack != NULL)
	{
		info = stack->info;
	}
	return info;
}

Student* popNode(StackNode** stack)
{
	Student* info = NULL;
	if ((*stack) != NULL)
	{
		info = (*stack)->info;
		StackNode* tmp = (*stack);
		(*stack) = tmp->next;
		free(tmp);
	}
	return info;
}

void deleteStack(StackNode** stack)
{
	while ((*stack))
	{
		Student* info = popNode(stack);
		printStudent(info);
		deleteStudent(info);
	}
}

void displayStack(StackNode** stack)
{
	StackNode* tmpStack = NULL;
	while ((*stack))
	{
		// get info by popping
		Student* info = popNode(stack);
		printStudent(info);
		// pushing info back on stack, reversing the order of elements
		// from original stack
		tmpStack = pushNode(tmpStack, info);
	}
	while (tmpStack)
	{
		// restore the original order of elements in the stack
		Student* info = popNode(&tmpStack);
		*stack = pushNode(*stack, info);
	}
}