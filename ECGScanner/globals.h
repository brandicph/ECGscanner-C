#ifndef GLOBALS_H
#define GLOBALS_H

//includes
#include <stdio.h>

//public variables
int GLOBAL_DEBUG;
int GLOBAL_TEST;
unsigned long int GLOBAL_COUNT;
int GLOBAL_SAMPLE_RATE;
int GLOBAL_SENSOR_ACTIVE;
char GLOBAL_SENSOR_INPUT[];

//public prototypes
unsigned long int global_count();

#endif