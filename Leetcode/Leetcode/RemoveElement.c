#include "main.h"

// Leetcode #27
// Remove all occurrences of a given integer (val) from an array (nums) in-place
// Function returns the number of elements which are not equal to val 

// Time complexity: O(n)
// Space complexity: O(1)

int removeElement(int** nums, int numsSize, int val)
{
	if (numsSize == 0 || (*nums) == NULL)
		return 0;
	int k = 0;
	for (int i = 0; i < numsSize; i++)
	{
		if ((*nums)[i] != val)
		{
			(*nums)[k] = (*nums)[i];
			k++;
		}
	}
	return k;
}

void main()
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
	int k = removeElement(&nums, numsSize, 3);
	printf("\nFound %d elements not equal to 3.", k);
	for (int i = 0; i < k; i++)
	{
		printf("\nElement %d: ", i + 1);
		printf("%d", nums[i]);
	}
}