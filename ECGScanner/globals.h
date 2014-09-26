#ifndef GLOBALS_H
#define GLOBALS_H

//includes
#include <stdio.h>

//public variables
int GLOBAL_DEBUG;
unsigned long int GLOBAL_COUNT;
int GLOBAL_SAMPLE_RATE;
int GLOBAL_SENSOR_ACTIVE;
char GLOBAL_SENSOR_INPUT[];

//public prototypes
int global_count();

#endif