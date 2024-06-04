#pragma once
#include "DataUtil.h"

#define PQUEUE_SIZE 7

// MAX PQUEUE IMPLEMENTATION

// currentIndex: no of elements in the PQueue
// size: max no of elements that can be added in the PQueue
typedef struct PQueue
{
	Student** items;
	int size;
	int currentIndex;
} PQueue;

void ReheapUp(Student** items, int currentIndex)
{
	if (currentIndex > 0)
	{
		int parentIndex = (currentIndex - 1) / 2;
		if (items[parentIndex]->income < items[currentIndex]->income)
		{
			Student* aux = items[parentIndex];
			items[parentIndex] = items[currentIndex];
			items[currentIndex] = aux;
			ReheapUp(items, parentIndex);
		}
	}
}

void enqueue(PQueue* pQueue, Student* info)
{
	if ((*pQueue).items == NULL)
	{
		(*pQueue).items = (Student**)malloc(sizeof(Student*) * PQUEUE_SIZE);
		memset((*pQueue).items, 0, sizeof(Student*) * PQUEUE_SIZE);
		(*pQueue).size = PQUEUE_SIZE;
	}

	if ((*pQueue).size > (*pQueue).currentIndex)
	{
		(*pQueue).items[(*pQueue).currentIndex] = info;
		ReheapUp((*pQueue).items, (*pQueue).currentIndex);
		(*pQueue).currentIndex++;
	}
}

void ReheapDown(PQueue* pQueue, int parentIndex)
{
	int lChildIndex = 2 * parentIndex + 1;
	int rChildIndex = 2 * parentIndex + 2;
	int maxIndex = parentIndex;

	if (lChildIndex < pQueue->currentIndex)
	{
		if (pQueue->items[lChildIndex]->income > pQueue->items[maxIndex]->income)
		{
			maxIndex = lChildIndex;
		}

		if (rChildIndex<pQueue->currentIndex
			&& pQueue->items[rChildIndex]->income > pQueue->items[maxIndex]->income)
		{
			maxIndex = rChildIndex;
		}

		if (maxIndex != parentIndex)
		{
			Student* aux = pQueue->items[maxIndex];
			pQueue->items[maxIndex] = pQueue->items[parentIndex];
			pQueue->items[parentIndex] = aux;
			ReheapDown(pQueue, maxIndex);
		}
	}
}

Student* deque(PQueue* pQueue)
{
	Student* result = NULL;

	if (pQueue->currentIndex > 0)
	{
		result = pQueue->items[0];
		pQueue->items[0] = pQueue->items[pQueue->currentIndex - 1];
		pQueue->currentIndex--;
		ReheapDown(pQueue, 0);
	}

	return result;
}

// change priority of PQueue: if the student's new income is higher than
// the old one => ReheapUp operation; if the new income is lower => ReheapDown operation
void changePrio(PQueue* pQueue, int index, float newIncome)
{
	if (index < 0 || index >= pQueue->currentIndex)
	{
		return;
	}

	float oldIncome = pQueue->items[index]->income;
	pQueue->items[index]->income = newIncome;

	if (newIncome > oldIncome)
	{
		ReheapUp(pQueue->items, index);
	}
	else if (newIncome < oldIncome)
	{
		ReheapDown(pQueue, index);
	}
}