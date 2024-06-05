#define LINE_SIZE 256
#include "HashTable.h"

void main()
{
	HashNode** hashTable = NULL;
	FILE* pFile = fopen("Data2.txt", "r");
	if (pFile)
	{
		char delimiter[] = ",\n";
		char* token = NULL;
		unsigned short floor, roomNo;
		char buffer[LINE_SIZE], roomType[LINE_SIZE];
		double price;

		while (fgets(buffer, sizeof(buffer), pFile))
		{
			token = strtok(buffer, delimiter);
			floor = atoi(token);
			token = strtok(NULL, delimiter);
			roomNo = atoi(token);
			token = strtok(NULL, delimiter);
			strcpy(roomType, token);
			token = strtok(NULL, delimiter);
			price = atof(token);
			Room* room = createRoom(floor, roomNo, roomType, price);
			putHT(&hashTable, room);
		}
	}
	displayHT(hashTable);
	int noRooms = 0;
	getNoRooms(hashTable, 4, &noRooms);
	printf("\nNo rooms: %d\n", noRooms);
	Node* head = createDLL(hashTable, 350);

	char roomType[] = "Single";
	deleteByRoomType(&head, roomType);
	printf("\n");
	printDLL(head);
}