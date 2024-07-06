#define _CRT_SECURE_NO_WARNINGS
#define LINE_SIZE 256
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

typedef struct Rezervare
{
	unsigned int id;
	char* hotel;
	unsigned char nrCamere;
	char* numeClient;
	float suma;
} Rezervare;

Rezervare* creareRezervare(unsigned int id, const char* hotel, unsigned char nrCamere, const char* numeClient,
	float suma)
{
	Rezervare* rezervare = (Rezervare*)malloc(sizeof(Rezervare));
	rezervare->id = id;
	rezervare->hotel = (char*)malloc(strlen(hotel) + 1);
	strcpy(rezervare->hotel, hotel);
	rezervare->nrCamere = nrCamere;
	rezervare->numeClient = (char*)malloc(strlen(numeClient) + 1);
	strcpy(rezervare->numeClient, numeClient);
	rezervare->suma = suma;
	return rezervare;
}

void afisareRezervare(Rezervare* rezervare)
{
	if (rezervare)
	{
		printf("Id: %d, Hotel: %s, Nr camere: %d, Nume client: %s, Suma: %.2f\n",
			rezervare->id, rezervare->hotel, rezervare->nrCamere, rezervare->numeClient,
			rezervare->suma);
	}
}

void stergereRezervare(Rezervare* rezervare)
{
	if (rezervare)
	{
		free(rezervare->hotel);
		free(rezervare->numeClient);
		free(rezervare);
	}
}

typedef struct TreeN
{
	struct TreeN* left;
	Rezervare* info;
	struct TreeN* right;
} TreeNode;

TreeNode* creareNod(Rezervare* rezervare)
{
	TreeNode* nod = NULL;

	if (rezervare)
	{
		nod = (TreeNode*)malloc(sizeof(TreeNode));
		nod->info = rezervare;
		nod->left = nod->right = NULL;
	}

	return nod;
}

void upsert(TreeNode** root, Rezervare* rezervare)
{
	if (*root == NULL)
	{
		TreeNode* nod = creareNod(rezervare);
		(*root) = nod;
	}
	else
	{
		if ((*root)->info->id > rezervare->id)
			upsert(&(*root)->left, rezervare);
		else if ((*root)->info->id < rezervare->id)
			upsert(&(*root)->right, rezervare);
		else
		{
			printf("Key already exists, updating it!\n");
			(*root)->info = rezervare;
		}
	}
}

void afisareArbore(TreeNode* root, int nivel)
{
	if (root)
	{
		for (int i = 0; i < nivel; i++)
			printf("\t");

		nivel++;
		printf("%d: %d camere\n", root->info->id, root->info->nrCamere);

		afisareArbore(root->left, nivel);
		afisareArbore(root->right, nivel);
	}
	else
	{
		for (int i = 0; i < nivel; i++)
			printf("\t");
		printf("NULL\n");
	}
}

// 2.
void calcNrCamere(TreeNode* root, int* nrTotalCamere)
{
	if (root == NULL)
		return;

	if (root && root->left == NULL && root->right == NULL)
		(*nrTotalCamere) += root->info->nrCamere;

	calcNrCamere(root->left, nrTotalCamere);
	calcNrCamere(root->right, nrTotalCamere);
}

// 3.
int calcInaltimeArbore(TreeNode* root)
{
	if (root == NULL)
		return 0;

	return 1 + max(calcInaltimeArbore(root->left), calcInaltimeArbore(root->right));
}

// 4.
void stergereNod(TreeNode** root, TreeNode** rsubTree)
{
	if ((*rsubTree)->left)
		stergereNod(root, &(*rsubTree)->left);
	else
	{
		stergereRezervare((*root)->info);
		(*root)->info = (*rsubTree)->info;

		TreeNode* tmp = *rsubTree;
		*rsubTree = tmp->right;
		free(tmp);
	}
}

void stergereNodRad(TreeNode** root)
{
	if (*root)
	{
		if ((*root)->left == NULL && (*root)->right == NULL)
		{
			stergereRezervare((*root)->info);
			free(*root);
			*root = NULL;
		}
		else if ((*root)->left == NULL || (*root)->right == NULL)
		{
			TreeNode* tmp = *root;
			*root = (*root)->left ? (*root)->left : (*root)->right;
			stergereRezervare(tmp->info);
			free(tmp);
		}
		else
		{
			stergereNod(root, &(*root)->right);
		}
	}
}

void inorder(TreeNode* root)
{
	if (root)
	{
		inorder(root->left);
		afisareRezervare(root->info);
		inorder(root->right);
	}
}

// 5.
unsigned int* expand(unsigned int* vectorId, int noEl)
{
	unsigned int* result = (unsigned int*)malloc(sizeof(unsigned int) * (noEl + 1));

	for (int i = 0; i < noEl; i++)
		result[i] = vectorId[i];

	return result;
}

void salvareIdVector(TreeNode* root, unsigned int** vectorId, int* noEl, unsigned int id)
{
	if (root)
	{
		if (root->info->id > id)
			salvareIdVector(root->left, vectorId, noEl, id);
		else if (root->info->id < id)
			salvareIdVector(root->right, vectorId, noEl, id);
		else
		{
			*vectorId = (unsigned int*)malloc(sizeof(unsigned int));
			(*vectorId)[(*noEl)++] = root->info->id;
		}

		if (root->info->id != id)
		{
			*vectorId = expand(*vectorId, *noEl);
			(*vectorId)[(*noEl)++] = root->info->id;
		}
	}
}

void rezervare()
{
	TreeNode* root = NULL;

	FILE* pFile = fopen("DataRezervare.txt", "r");
	if (pFile)
	{
		char delimiter[] = ",\n";
		char* token = NULL;
		char buffer[LINE_SIZE], hotel[LINE_SIZE], numeClient[LINE_SIZE];
		unsigned int id;
		unsigned char nrCamere;
		float suma;

		while (fgets(buffer, sizeof(buffer), pFile))
		{
			token = strtok(buffer, delimiter);
			id = atoi(token);
			token = strtok(NULL, delimiter);
			strcpy(hotel, token);
			token = strtok(NULL, delimiter);
			nrCamere = atoi(token);
			token = strtok(NULL, delimiter);
			strcpy(numeClient, token);
			token = strtok(NULL, delimiter);
			suma = atof(token);

			Rezervare* rezervare = creareRezervare(id, hotel, nrCamere, numeClient, suma);
			upsert(&root, rezervare);
		}
		afisareArbore(root, 0);

		// 2.
		int nrCam = 0;
		calcNrCamere(root, &nrCam);
		printf("\nNr camere din nodurile frunza: %d\n", nrCam);

		// 3.
		int inaltimeArbore = calcInaltimeArbore(root);
		printf("\nInaltime arbore: %d\n", inaltimeArbore);

		// 4.
		stergereNodRad(&root);
		afisareArbore(root, 0);
		inorder(root);

		// 5.
		unsigned int* vectorId = NULL;
		int noEl = 0;
		salvareIdVector(root, &vectorId, &noEl, 89);
		printf("\n\n-----------------------------------\n");
		for (int i = 0; i < noEl; i++)
			printf("Id: %d\n", vectorId[i]);
	}
}