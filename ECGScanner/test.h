#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "utils.h"

static int getNextData(); // Please implement me in Sensor.c
extern void testData(char *filename, int actual);

typedef struct Test {
	FILE *file;
	int value;
	int read;
	int errors;
} Test;

int run_Test(Test *t, char *filename, int actual);


#endif
