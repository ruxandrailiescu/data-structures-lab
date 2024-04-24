#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

union Reference {
	unsigned char intRef;
	unsigned short extRef;
};

typedef union Reference reference;

typedef struct student {
	char* name;
	float income;
	reference reference;
}Student;

Student* createStudent(const char* name, float income, unsigned short ref) {
	Student* student = NULL;

	student = (Student*)malloc(sizeof(Student));

	student->name = (char*)malloc(strlen(name) + 1);

	strcpy(student->name, name);

	student->income = income;

	student->reference.extRef = ref;

	return student;
}

void printStudent(Student* stud)
{
	if (stud != NULL)
	{
		printf("Name: %s, income: %f\n", stud->name, stud->income);
		if (stud->reference.extRef >> 15 == 1)
		{
			short uid = stud->reference.extRef >> 8 & 127;
			printf("University ref: %d\n", uid);
			printf("External ref: %d\n", stud->reference.extRef & 255);
		}
		else
		{
			printf("Internal ref: %d\n", stud->reference.intRef);
		}
	}
}

void deleteStudent(Student* stud)
{
	if (stud != NULL)
	{
		free(stud->name);
		free(stud);
	}
}