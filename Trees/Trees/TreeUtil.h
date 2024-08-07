#pragma once
#include "DataUtil.h"

typedef struct TreeN
{
	struct TreeN* left;
	Student* info;
	struct TreeN* right;
	int bFactor;
}TreeNode, * PTreeNode;

TreeNode* createTreeNode(Student* info)
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->info = info;
	node->left = node->right = NULL;
	node->bFactor = 0;
	return node;
}

Student* getMax(TreeNode* root)
{
	while (root->right)
		root = root->right;
	return root->info;
}

void postorder(TreeNode* root)
{
	if (root)
	{
		postorder(root->left);
		postorder(root->right);
		printf("Student: %s, reference: %d\n", root->info->name, root->info->reference.intRef);

	}
}

void inorder(TreeNode* root)
{
	if (root)
	{
		inorder(root->left);
		printf("Student: %s, reference: %d\n", root->info->name, root->info->reference.intRef);
		inorder(root->right);
	}
}

void preorder(TreeNode* root)
{
	if (root)
	{
		printf("Student: %s, reference: %d\n", root->info->name, root->info->reference.intRef);
		preorder(root->left);
		preorder(root->right);
	}
}

int maxF(int x, int y)
{
	return x > y ? x : y;
}

int getHeight(TreeNode* root)
{
	if (root == NULL)
		return 0;
	else
	{
		return 1 + maxF(getHeight(root->left), getHeight(root->right));
	}
}

TreeNode* rightRotation(TreeNode* pivot)
{
	TreeNode* desc = pivot->left;
	pivot->left = desc->right;
	desc->right = pivot;
	return desc;
}

TreeNode* leftRotation(TreeNode* pivot)
{
	TreeNode* desc = pivot->right;
	pivot->right = desc->left;
	desc->left = pivot;
	return desc;
}

void rebalance(TreeNode** root)
{
	(*root)->bFactor = getHeight((*root)->right) - getHeight((*root)->left);
	if ((*root)->bFactor == 2)
	{
		TreeNode* desc = (*root)->right;
		if (desc->bFactor == -1)
			(*root)->right = rightRotation(desc);
		*root = leftRotation(*root);
	}
	else if ((*root)->bFactor == -2)
	{
		TreeNode* desc = (*root)->left;
		if (desc->bFactor == 1)
			(*root)->left = leftRotation(desc);
		*root = rightRotation(*root);
	}
}

void upsert(TreeNode** root, Student* info)
{
	if (*root == NULL)
	{
		TreeNode* node = createTreeNode(info);
		*root = node;
	}
	else
	{
		if ((*root)->info->reference.intRef > info->reference.intRef)
			upsert(&(*root)->left, info);
		else if ((*root)->info->reference.intRef < info->reference.intRef)
			upsert(&(*root)->right, info);
		else
		{
			printf("Key already exists, updating it!");
			(*root)->info = info;
		}
	}
	rebalance(root);
}

void DisplayTreeStructure(TreeNode* root, int level)
{
	if (root != NULL)
	{
		for (int i = 0; i < level; i++)
			printf("\t");
		printf("%s:%d\n", root->info->name, root->info->reference.intRef);
		level++;
		DisplayTreeStructure(root->left, level);
		DisplayTreeStructure(root->right, level);
	}
	else
	{
		for (int i = 0; i < level; i++)
			printf("\t");
		printf("NULL\n");
	}
}

void deleteFullNode(TreeNode** root, TreeNode** rSubTree)
{
	if ((*rSubTree)->left)
		deleteFullNode(root, &(*rSubTree)->left);
	else
	{
		deleteStudent((*root)->info);
		(*root)->info = (*rSubTree)->info;
		TreeNode* tmp = *rSubTree;
		(*rSubTree) = tmp->right;
		free(tmp);
	}
}

void deleteNodeByKey(TreeNode** root, unsigned char key)
{
	if (*root != NULL)
	{
		if ((*root)->info->reference.intRef > key)
			deleteNodeByKey(&(*root)->left, key);
		else if ((*root)->info->reference.intRef < key)
			deleteNodeByKey(&(*root)->right, key);
		else //we have found the key
		{
			//the node is a leaf
			if ((*root)->left == NULL && (*root)->right == NULL)
			{
				deleteStudent((*root)->info);
				free(*root);
				*root = NULL;
			}
			// the node has 1 descendant
			else if ((*root)->left == NULL || (*root)->right == NULL)
			{
				TreeNode* tmp = *root;
				*root = (*root)->left ? (*root)->left : (*root)->right;
				deleteStudent(tmp->info);
				free(tmp);
			}
			// the node has 2 descendants
			else
			{
				deleteFullNode(root, &(*root)->right);
			}
		}
	}
	// rebalance after deleting a node -- corner cases
}

/*
	Write a function that counts how many nodes
	have keys that are greater than a value
	passed as a parameter
	hint: starting from getHeight function
*/

void countNodesGreaterThan(TreeNode* root, unsigned char key, int* count)
{
	if (root == NULL)
	{
		return;
	}

	if (root->info->reference.intRef > key)
	{
		(*count)++;
	}

	countNodesGreaterThan(root->left, key, count);
	countNodesGreaterThan(root->right, key, count);
}

//int countNodesGreaterThan(TreeNode* root, unsigned char key)
//{
//	if (root->info->reference.intRef > key)
//	{
//		return getHeight(root);
//	}
//	else if (root->info->reference.intRef < key)
//	{
//		countNodesGreaterThan(root->left, key);
//	}
//}

//void countNodesGreaterThan(TreeNode* root, unsigned char key, int* count)
//{
//	if (root == NULL)
//	{
//		return;
//	}
//	
//	if (root->info->reference.intRef > key)
//	{
//		(*count) += getHeight(root->left) + getHeight(root->right);
//	}
//}