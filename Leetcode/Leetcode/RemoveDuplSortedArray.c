#include "main.h"

// Leetcode #26
// Remove duplicates from a sorted integer array in-place
// Function returns the number of unique elements

// Time complexity: O(n)
// Space complexity: O(1)

int removeDuplicates(int** nums, int numsSize)
{
	if (numsSize == 0 || (*nums) == NULL)
		return 0;

	int k = 1;
	
	for (int i = 1; i < numsSize; i++)
	{
		if ((*nums)[i] != (*nums)[k - 1])
		{
			(*nums)[k] = (*nums)[i];	// position k will be filled with the next unique element
			k++;
		}
	}
	return k;
}

void mainRD()
{
	int* nums = NULL;
	int numsSize = 0;
	printf("Enter number of elements in array: ");
	scanf("%d", &numsSize);
	nums = (int*)malloc(sizeof(int) * numsSize);
	for (int i = 0; i < numsSize; i++)
	{
		printf("\nEnter element %d: ", i + 1);
		scanf("%d", &nums[i]);
	}
	int k = removeDuplicates(&nums, numsSize);
	printf("\nFound %d unique elements.", k);
	for (int i = 0; i < k; i++)
	{
		printf("\nElement %d: ", i + 1);
		printf("%d", nums[i]);
	}
}