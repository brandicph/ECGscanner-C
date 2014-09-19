#ifndef SENSOR_H
#define SENSOR_H

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int getNextData(); // Please implement me in Sensor.c
int lowPassFilter(int ym1, int ym2, int xm0, int xm6, int xm12);
int highPassFilter(int ym0, int xm0, int xm16, int xm17, int xm32);
int derivativeFilter(int xm0, int xm1, int xm3, int xm4);
int squaredFilter(int xm0);
int movingWindow(int ym0, int xold, int xnew, int N);
int movAvg(int ym0, int xold, int xnew, int N);
int peakDetection(int xm1, int x, int xp1);

#endif
