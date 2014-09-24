#ifndef SENSOR_H
#define SENSOR_H

#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "utils.h"

static int isPeak(int *x);
static int searchBack();
static int getPeak();
static int nextValue(int value);
static void saveRRInRR_Recent(int RR);
static void saveRRInRR_Recent_OK(int RR);
static void savePeak(int peak);
static int calculateRR();
static int count_peak();
static int count_Rpeak();
static int count_interval();
static int isPeak(int value);
static int calcMovingAvg(int latest_avg, int temp, int value, int N);

extern int detection(int value);

#endif