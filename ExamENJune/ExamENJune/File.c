#define _CRT_SECURE_NO_WARNINGS
#define LINE_SIZE 256
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

// 1.
typedef struct File
{
	char* identifier;
	unsigned int size;
	bool readOnly;
	char createdDate[10];
	char* owner;
} File;

File* createFile(const char* identifier, unsigned int size, bool readOnly, const char* createdDate, const char* owner)
{
	File* file = NULL;

	if (identifier && createdDate && owner && (strlen(createdDate) == 10))
	{
		file = (File*)malloc(sizeof(File));
		file->identifier = (char*)malloc(strlen(identifier) + 1);
		strcpy(file->identifier, identifier);
		file->size = size;
		file->readOnly = readOnly;
		strcpy(file->createdDate, createdDate);
		file->owner = (char*)malloc(strlen(owner) + 1);
		strcpy(file->owner, owner);
	}

	return file;
}

void displayFile(File* file)
{
	if (file)
	{
		printf("Identifier: %s, Size: %d, Read Only: %s, Created Date: %s, Owner: %s\n",
			file->identifier, file->size, (file->readOnly ? "true" : "false"), file->createdDate, file->owner);
	}
}

void deleteFile(File* file)
{
	if (file)
	{
		free(file->identifier);
		free(file->owner);
		free(file);
	}
}

typedef struct TreeN
{
	struct TreeN* left;
	File* info;
	struct TreeN* right;
} TreeNode;

TreeNode* createTreeNode(File* file)
{
	TreeNode* node = NULL;

	if (file)
	{
		node = (TreeNode*)malloc(sizeof(TreeNode));
		node->info = file;
		node->left = node->right = NULL;
	}

	return node;
}

// insert function -- RECURSIVE FUNCTION
void upsert(TreeNode** root, File* file)
{
	if (*root == NULL)
	{
		TreeNode* node = createTreeNode(file);
		*root = node;
	}
	else
	{
		// insert based on the conditions imposed by BST theory
		if (strcmp((*root)->info->identifier, file->identifier) > 0)	// node is smaller, go left
		{
			upsert(&(*root)->left, file);
		}
		else if (strcmp((*root)->info->identifier, file->identifier) < 0)	// node is greater, go right
		{
			upsert(&(*root)->right, file);
		}
		else
		{
			printf("Key already exists, updating it!");
			(*root)->info = file;
		}
	}
}

void displayTree(TreeNode* root, int level)
{
	if (root)
	{
		for (int i = 0; i < level; i++)
		{
			printf("\t");
		}
		printf("%s\n", root->info->identifier);
		
		level++;
		displayTree(root->left, level);
		displayTree(root->right, level);
	}
	else
	{
		for (int i = 0; i < level; i++)
		{
			printf("\t");
		}
		printf("NULL\n");
	}
}

// 2.
void displayGreaterThanDate(TreeNode* root, const char* date)
{
	if (root == NULL)
	{
		return;
	}

	if (strcmp(root->info->createdDate, date) > 0)
	{
		displayFile(root->info);
	}

	displayGreaterThanDate(root->left, date);
	displayGreaterThanDate(root->right, date);
}

// 3.
void countFilesReadOnly(TreeNode* root, int* num)
{
	if (root == NULL)
	{
		return;
	}

	if (root->info->readOnly == true)
	{
		(*num)++;
	}

	countFilesReadOnly(root->left, num);
	countFilesReadOnly(root->right, num);
}

// 4.
double calcSizeAndCount(TreeNode* root, int* filesCount)
{
	if (root == NULL)
	{
		return 0;
	}

	double totalSize = root->info->size;
	(*filesCount)++;

	totalSize += calcSizeAndCount(root->left, filesCount);
	totalSize += calcSizeAndCount(root->right, filesCount);

	return totalSize;
}

double avgFileSize(TreeNode* root, int* filesCount)
{
	double totalSize = calcSizeAndCount(root, filesCount);
	if ((*filesCount) == 0)
	{
		return 0.0;
	}
	return totalSize / (*filesCount);
}

// 5.


void main()
{
	TreeNode* root = NULL;

	FILE* pFile = fopen("DataFile.txt", "r");
	if (pFile)
	{
		char delimiters[] = ",\n";
		char* token = NULL;
		char buffer[LINE_SIZE];
		char identifier[LINE_SIZE], createdDate[LINE_SIZE], owner[LINE_SIZE];
		unsigned int size;
		bool readOnly;

		while (fgets(buffer, sizeof(buffer), pFile))
		{
			readOnly = false;
			token = strtok(buffer, delimiters);
			strcpy(identifier, token);
			token = strtok(NULL, delimiters);
			size = atoi(token);
			token = strtok(NULL, delimiters);
			if (strcmp("true", token) == 0)
			{
				readOnly = true;
			}
			token = strtok(NULL, delimiters);
			strcpy(createdDate, token);
			token = strtok(NULL, delimiters);
			strcpy(owner, token);

			File* file = createFile(identifier, size, readOnly, createdDate, owner);
			//displayFile(file);
			upsert(&root, file);
		}
		fclose(pFile);
	}

	displayTree(root, 0);

	// 2.
	displayGreaterThanDate(root, "2023/12/13");

	// 3.
	int filesReadOnly = 0;
	countFilesReadOnly(root, &filesReadOnly);
	printf("\nNum of files with read only access: %d\n", filesReadOnly);

	// 4.
	int filesCount = 0;
	double avgSize = avgFileSize(root, &filesCount);
	printf("\nAvg file size: %.2f\n", avgSize);
}