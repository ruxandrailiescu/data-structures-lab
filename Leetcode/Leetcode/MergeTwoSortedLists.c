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
	
	if (list1 == NULL && list2 == NULL) {
		return NULL;
	}
	else if (list1 != NULL && list2 == NULL) {
		return list1;
	}
	else if (list2 != NULL && list1 == NULL) {
		return list2;
	}

	struct ListNode* tmp = NULL;
	if (list1->val < list2->val) {
		tmp = list1;
		list1 = list1->next;
	}
	else {
		tmp = list2;
		list2 = list2->next;
	}

	struct ListNode* root = tmp;
	while ((list1 != NULL) || (list2 != NULL)) {
		if ((list2 == NULL) || ((list1 != NULL) && (list1->val < list2->val))) {
			tmp->next = list1;
			list1 = list1->next;
		}
		else {
			tmp->next = list2;
			list2 = list2->next;
		}
		tmp = tmp->next;
	}
	return root;
}