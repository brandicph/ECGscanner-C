#ifndef FILTERS_H
#define FILTERS_H

//includes
#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "utils.h"
#include "test.h"

//private prototypes
static int lowPassFilter(int *x, int *y);
static int highPassFilter(int *x, int *y);
static int derivativeFilter(int *x);
static int squaredFilter(int *x);
static int movingWindow(int ym0, int N);

//public prototypes
int filter(int value);

#endif