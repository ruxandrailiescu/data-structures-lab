#pragma once
#include "DataUtil.h"

typedef struct NodeS
{
	Student* info;
	struct NodeS* next;
} StackNode;

StackNode* createNodeStack(Student* info)
{
	StackNode* node = (StackNode*)malloc(sizeof(StackNode));
	node->info = info;
	node->next = NULL;
	return node;
}

void pushNodeStack(StackNode** stack, Student* info)
{
	StackNode* node = createNodeStack(info);
	node->next = (*stack);
	(*stack) = node;
}

Student* peekNodeStack(StackNode* stack)
{
	Student* info = NULL;
	if (stack != NULL)
		info = stack->info;
	return info;
}

Student* popNodeStack(StackNode** stack)
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
	while (*stack)
	{
		Student* info = popNodeStack(stack);
		printStudent(info);
		deleteStudent(info);
	}
}

void displayStack(StackNode** stack)
{
	StackNode* tmpStack = NULL;
	while (*stack)
	{
		Student* info = popNodeStack(stack);
		printStudent(info);
		pushNodeStack(&tmpStack, info);
	}
	
	while (tmpStack)
	{
		Student* info = popNodeStack(&tmpStack);
		pushNodeStack(stack, info);
	}
}