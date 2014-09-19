//utils.h : Header file for UTILS.C
#ifndef UTILS_H
#define UTILS_H

#pragma region Headers
#include <stdio.h>
#pragma endregion Reference any additional headers in this file


#pragma region Public structures
typedef struct
{
	int i;
	char c;
} MyStruct;
#pragma endregion Public structures regarding the UTILS.C


#pragma region Prototypes

void queue(int *queue, int arrSize, int item);
int mod(int a, int b);
void readObject(MyStruct ms);

#pragma endregion Prototypes bla bla

#endif
