#include "main.h"

// Leetcode #1929

// Time complexity: O(n)
// Space complexity: O(n)


int* getConcatenation(int* nums, int numsSize)
{
	if (numsSize == 0 || nums == NULL)
		return NULL;

	int* ans = (int*)malloc(sizeof(int) * (2 * numsSize));
	int j = 0;
	do
	{
		for (int i = 0; i < numsSize; i++)
		{
			ans[j] = nums[i];
			j++;
		}
	} while (j < (2 * numsSize));
	return ans;
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
	int* ans = getConcatenation(nums, numsSize);
	for (int i = 0; i < 2 * numsSize; i++)
	{
		printf("\nElement %d: ", i + 1);
		printf("%d", ans[i]);
	}
}