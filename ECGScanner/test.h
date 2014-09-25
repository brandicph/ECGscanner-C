#ifndef TEST_H
#define TEST_H

#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "utils.h"

static int getNextData();

typedef struct Test {
	FILE *file;
	int value;
	int read;
	int errors;
} Test;

Test TEST_LOW;
Test TEST_HIGH;
Test TEST_DER;
Test TEST_SQR;
Test TEST_MWI;

int run_Test(Test *t, char *filename, int actual);
void testResults();


#endif
