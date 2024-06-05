#pragma once
#include "DataUtil.h"

typedef struct TreeN
{
	struct TreeN* left;
	Student* info;
	struct TreeN* right;
	int bFactor;
} TreeNode;

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
	// postorder traversal: left, right, root / right, left, root
	if (root)
	{
		postorder(root->left);
		postorder(root->right);
		printf("Student: %s, reference: %d\n", root->info->name, root->info->reference.intRef);
	}
}

void inorder(TreeNode* root)
{
	// inorder traversal: left, root, right / right, root, left
	// if left = min and right = max => first inorder traversal <=> ascending order
	//								 => second inorder traversal <=> descending order
	if (root)
	{
		inorder(root->left);
		printf("Student: %s, reference: %d\n", root->info->name, root->info->reference.intRef);
		inorder(root->right);
	}
}

void preorder(TreeNode* root)
{
	// preorder traversal: root, left, right / root, right, left
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

//void rebalance(TreeNode** root)
//{
//	(*root)->bFactor
//}

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
//	rebalance(root);
}