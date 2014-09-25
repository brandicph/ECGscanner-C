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
	int value1;
	int value2;
	int read;
	int errors;
} Test;

Test TEST_LOW;
Test TEST_HIGH;
Test TEST_DER;
Test TEST_SQR;
Test TEST_MWI;
Test TEST_RPEAK;

static void init_Test(Test *t, char *filename);

void run_TestPeak(Test *t, char *filename, int actual1, int actual2);
void run_TestFilter(Test *t, char *filename, int actual);
void testResults();


#endif
