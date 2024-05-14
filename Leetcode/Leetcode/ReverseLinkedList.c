#include "main.h"

// Leetcode #206

/*
	Given the head of a singly linked list, reverse the list, and return the reversed list.
	Time complexity: O(n)
	Space complexity: O(1)
*/

// Definition for singly-linked list
struct ListNode {
	int val;
	struct ListNode* next;
};

struct ListNode* reverseList(struct ListNode* head) {
	
	struct ListNode* current = head;
	struct ListNode* next = NULL;
	struct ListNode* prev = NULL;

	while (current) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	return prev;
}