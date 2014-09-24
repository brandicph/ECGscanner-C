//filter.h : Header file for FILTER.C
#ifndef FILTERS_H
#define FILTERS_H

#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "utils.h"
#include "test.h"

static int lowPassFilter(int *x, int *y);
static int highPassFilter(int *x, int *y);
static int derivativeFilter(int *x);
static int squaredFilter(int *x);
static int movingWindow(int ym0, int N);

extern int filter(int value);

#endif