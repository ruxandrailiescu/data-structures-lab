#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define HASHT_SIZE 26
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Room
{
	unsigned short floor;
	unsigned short roomNo;
	char* roomType;
	double price;
} Room;

typedef struct HashNode
{
	Room* info;
	struct HashNode* next;
} HashNode;

int fHash(unsigned short floor)
{
	return floor % HASHT_SIZE;
}

Room* createRoom(unsigned short floor, unsigned short roomNo, const char* roomType, double price)
{
	Room* room = (Room*)malloc(sizeof(Room));
	room->floor = floor;
	room->roomNo = roomNo;
	room->roomType = (char*)malloc(strlen(roomType) + 1);
	strcpy(room->roomType, roomType);
	room->price = price;
	return room;
}

void displayRoom(Room* room)
{
	if (room)
	{
		printf("Floor: %d, Room no: %d, Room type: %s, Price: %f\n", 
			room->floor, room->roomNo, room->roomType, room->price);
	}
}

HashNode* createHashNode(Room* info)
{
	HashNode* node = (HashNode*)malloc(sizeof(HashNode));
	node->info = info;
	node->next = NULL;
	return node;
}

// insert function (collision avoidance mechanism => chaining)
void putHT(HashNode*** hashTable, Room* room)
{
	if (*hashTable == NULL)
	{
		(*hashTable) = (HashNode**)malloc(sizeof(HashNode*) * HASHT_SIZE);
		memset((*hashTable), 0, sizeof(HashNode*) * HASHT_SIZE);
	}

	HashNode* node = createHashNode(room);
	int hashValue = fHash(room->floor);
	node->next = (*hashTable)[hashValue];
	(*hashTable)[hashValue] = node;
}

void displayHT(HashNode** hashTable)
{
	if (hashTable)
	{
		for (int i = 0; i < HASHT_SIZE; i++)
		{
			printf("Index: %d\n", i);
			HashNode* current = hashTable[i];
			while (current)
			{
				displayRoom(current->info);
				current = current->next;
			}
		}
	}
}

void getNoRooms(HashNode** hashTable, unsigned short floor, int* noRooms)
{
	if (hashTable == NULL)
	{
		return;
	}
	else
	{
		int hashValue = fHash(floor);
		HashNode* current = hashTable[hashValue];
		while (current)
		{
			if (current->info->floor == floor)
			{
				(*noRooms)++;
			}
			current = current->next;
		}
	}
}

typedef struct NodeDL
{
	struct NodeDL* prev;
	Room* info;
	struct NodeDL* next;
} Node;

Node* createNodeDLL(Room* room)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->info = room;
	node->prev = node->next = NULL;
	return node;
}

void printDLL(Node* head)
{
	Node* current = head;
	while (current)
	{
		displayRoom(current->info);
		current = current->next;
	}
}

Node* createDLL(HashNode** hashTable, double price)
{
	Node* head = NULL;
	Node* tail = NULL;

	for (int i = 0; i < HASHT_SIZE; i++)
	{
		HashNode* current = hashTable[i];
		while (current)
		{
			if (current->info->price > price)
			{
				Node* node = createNodeDLL(current->info);
				if (!head)
				{
					head = node;
					tail = node;
				}
				else
				{
					tail->next = node;
					node->prev = tail;
					tail = node;
				}
			}
			current = current->next;
		}
	}
	printDLL(head);
	return head;
}

void deleteByRoomType(Node** head, const char* roomType)
{
	Node* current = *head;
	while (current)
	{
		if (strcmp(current->info->roomType, roomType) == 0)
		{
			if (current->prev)
			{
				current->prev->next = current->next;
			}
			else
			{
				*head = current->next;
			}

			if (current->next)
			{
				current->next->prev = current->prev;
			}
			Node* toDelete = current;
			current = current->next;
			free(toDelete->info->roomType);
			free(toDelete->info);
			free(toDelete);
		}
		else
		{
			current = current->next;
		}
	}
}