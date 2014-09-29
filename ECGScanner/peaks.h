#ifndef SENSOR_H
#define SENSOR_H

//includes
#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "utils.h"
#include "test.h"

//private prototypes
static int isPeak(int *x);
static int searchBack();
static int getPeak();
static int nextValue(int value);
static void saveRRInRR_Recent(int RR);
static void saveRRInRR_Recent_OK(int RR);
static void savePeak(int peak);
static int calculateRR();
static int count_miss();
static int count_peak();
static int count_Rpeak();
static int count_interval();
static int isPeak(int value);
static int calcMovingAvg(int latest_avg, int temp, int value, int N);

static void printWarning(char *message);
static void printStatus(int RR, int Rpeak);

//public prototypes
int detection(int value);

#endif