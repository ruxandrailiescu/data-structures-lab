#pragma once
#include "DataUtil.h"
#define HT_INITIAL_SIZE 3

typedef struct HTable
{
	Student** items;
	int size;
} HashTable;

void resizeHT(HashTable*);

void displayStudents(Student** agenda, int noEl)
{
	for (int i = 0; i < noEl; i++)
	{
		printf("Bucket %d:\n", i);
		printStudent(agenda[i]);
	}
}

int fhash(char key, int size)
{
	return key % size;
}

// for linear probing collision mechanism we need a resizing function for the hash table
int linearProbing(HashTable* hTable, char key, int index)
{
	while (hTable->items[index] != NULL)	// while we did not find an empty slot, increment the index
	{
		index++;
		if (hTable->size == index)	// if we reached the end of the table, resize
		{
			printf("\n---------------------------- Hash Table Items Before Resize ----------------------------\n");
			displayStudents(hTable->items, hTable->size);
			resizeHT(hTable);
			index = fhash(key, hTable->size);	// recalculate the index
		}
	}
	return index;
}

// insert function
void putHashTable(HashTable* hTable, Student* stud)
{
	if (hTable->size == 0)	// initializes the hash table if it is empty
	{
		hTable->items = (Student**)malloc(sizeof(Student*) * HT_INITIAL_SIZE);
		hTable->size = HT_INITIAL_SIZE;
		memset(hTable->items, 0, sizeof(Student*) * HT_INITIAL_SIZE);
	}

	int index = fhash(stud->reference.intRef, hTable->size);	// calculates the index using the hash function

	if (hTable->items[index] != NULL)	// if the index is occupied, it resolves the collision using linear probing
	{
		char key = stud->reference.intRef;
		index = linearProbing(hTable, key, index);
	}

	hTable->items[index] = stud;	// inserts the student at the calculated index
}

// resize function (when hash table is full -- needed for open-addressing collision mechanisms)
void resizeHT(HashTable* hTable)
{
	Student** aux = hTable->items;
	hTable->size *= 3;	// triples the size of the hash table
	hTable->items = (Student**)malloc(sizeof(Student*) * hTable->size);
	memset(hTable->items, 0, sizeof(Student*) * hTable->size);

	for (int index = 0; index < hTable->size / 3; index++)	// rehashes and inserts the existing students into the
															// new larger table
	{
		Student* stud = aux[index];
		if (stud != NULL)
		{
			putHashTable(hTable, stud);
		}
	}
}