#define _CRT_SECURE_NO_WARNINGS
#define LINE_SIZE 256
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


typedef struct Arrival
{
	char* trainCode;
	char* comingFrom;
	char* arrivalTime;
	unsigned short delay;
	unsigned short noPassengers;
} Arrival;


void main()
{

}