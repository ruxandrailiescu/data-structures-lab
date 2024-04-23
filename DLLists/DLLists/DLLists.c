#include "ListUtil.h"

void main()
{
	ListNode* headList = NULL;
	Student* stud1 = createStudent("Ruxandra Iliescu", 2500, 300);
	Student* stud2 = createStudent("Cristiana Girica", 2500, 100);
	Student* stud3 = createStudent("Ana Boncu", 2500, 200);
	insertHead(&headList, stud1);
	insertHead(&headList, stud3);
	insertHead(&headList, stud2);
	deleteNodeByKey(&headList, "Ana Boncu");
	printList(headList);
}