#include "main.h"

// Leetcode #21

/*
	You are given the heads of two sorted linked lists list1 and list2.

	Merge the two lists into one sorted list. 
	The list should be made by splicing together the nodes of the first two lists.

	Return the head of the merged linked list.
*/

struct ListNode {
	int val;
	struct ListNode* next;
};

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
	if (list1 == NULL)
		return list2;
	if (list2 == NULL)
		return list1;
}