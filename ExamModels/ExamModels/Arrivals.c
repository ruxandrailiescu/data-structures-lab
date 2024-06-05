#define LINE_SIZE 256
#include "BST.h"

void main()
{
	TreeNode* root = NULL;
	FILE* pFile = fopen("Data.txt", "r");
	if (pFile)
	{
		char delimiter[] = ", \n";
		char buffer[LINE_SIZE];
		char* token = NULL;
		char code[LINE_SIZE];
		char comingFrom[LINE_SIZE];
		char arrivalTime[LINE_SIZE];
		unsigned short delay;
		unsigned short passengers;
		while (fgets(buffer, sizeof(buffer), pFile))
		{
			token = strtok(buffer, delimiter);
			strcpy(code, token);
			token = strtok(NULL, delimiter);
			strcpy(comingFrom, token);
			token = strtok(NULL, delimiter);
			strcpy(arrivalTime, token);
			token = strtok(NULL, delimiter);
			delay = atoi(token);
			token = strtok(NULL, delimiter);
			passengers = atoi(token);
			Arrival* arrival = createArrival(code, comingFrom, arrivalTime, delay, passengers);
			upsert(&root, arrival);
		}
	}
	inorder(root);

	char* lastToArrive = getMax(root);
	printf("\n%s", lastToArrive);

	int delays = getDelays(root);
	printf("\nTrips with delays: %d", delays);

	int totalPass = getTotalPassengers(root, "Bucuresti");
	printf("\nTotal passengers for Bucuresti: %d", totalPass);

	int noEl = 0;
	Arrival** arrivalsPath = NULL;
	convertToArray(root, "13:37", &arrivalsPath, &noEl);

	for (int i = 0; i < noEl; i++)
	{
		printf("\n");
		displayArrival(arrivalsPath[i]);
	}
}