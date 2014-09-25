#ifndef TEST_H
#define TEST_H

#define _CRT_SECURE_NO_DEPRECATE //keep VS from complaining about fopen error C4996
#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "utils.h"

//Test structure
typedef struct Test {
	FILE *file; //file
	char *name; //name of test (displayname)
	int value1; //expected value
	int value2; //if two values pr line in testfile
	int read;	//EOF indicator
	int errors; //number of errors found
} Test;

//Test filters
Test TEST_LOW; 
Test TEST_HIGH;
Test TEST_DER;
Test TEST_SQR;
Test TEST_MWI;

//Test Rpeak
Test TEST_RPEAK;

//Initializer for Test structures
static void init_Test(Test *t, char *filename);

//Test functions
void run_TestPeak(Test *t, char *filename, int actual1, int actual2);
void run_TestFilter(Test *t, char *filename, int actual);

//Printing functions
void testResults();


#endif
