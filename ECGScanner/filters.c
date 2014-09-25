#include "filters.h"

#define MAX_X 13
#define MAX_LOW 33
#define MAX_HIGH 5
#define MAX_DER 1
#define MAX_SQR 30

static int x[MAX_X]			= { 0 };
static int low[MAX_LOW]		= { 0 };
static int high[MAX_HIGH]	= { 0 };
static int der[MAX_DER]		= { 0 };
static int sqr[MAX_SQR]		= { 0 };
static int mwi				= 0;

int lowPassFilter(int *x, int *y){
	int ym1 = y[mod(GLOBAL_COUNT - 1, MAX_LOW)];
	int ym2 = y[mod(GLOBAL_COUNT - 2, MAX_LOW)];
	int xm0 = x[mod(GLOBAL_COUNT, MAX_X)];
	int xm6 = x[mod(GLOBAL_COUNT - 6, MAX_X)];
	int xm12 = x[mod(GLOBAL_COUNT - 12, MAX_X)];
	return (2 * ym1 - ym2 + (xm0 - 2 * xm6 + xm12) / 32);
}

int highPassFilter(int *x, int *y){
	int ym1 = y[mod(GLOBAL_COUNT - 1, MAX_HIGH)];
	int xm0 = x[mod(GLOBAL_COUNT, MAX_LOW)];
	int xm16 = x[mod(GLOBAL_COUNT - 16, MAX_LOW)];
	int xm17 = x[mod(GLOBAL_COUNT - 17, MAX_LOW)];
	int xm32 = x[mod(GLOBAL_COUNT - 32, MAX_LOW)];
	return (ym1 - (xm0/32) + xm16 - xm17 + (xm32/ 32));
}

int derivativeFilter(int *x){
	int xm0 = x[mod(GLOBAL_COUNT, MAX_HIGH)];
	int xm1 = x[mod(GLOBAL_COUNT - 1, MAX_HIGH)];
	int xm3 = x[mod(GLOBAL_COUNT - 3, MAX_HIGH)];
	int xm4 = x[mod(GLOBAL_COUNT - 4, MAX_HIGH)];
	return ((2 * xm0 + xm1 - xm3 - 2 * xm4) / 8);
}

//save last value before override so we can calculate the mean O(c)
static int squared_old = 0;
static int squared_new = 0;
int squaredFilter(int *x, int *y){
	int xm0 = x[mod(GLOBAL_COUNT, MAX_DER)];
	squared_old = y[mod(GLOBAL_COUNT, MAX_SQR)];
	squared_new = xm0 * xm0;
	return squared_new;
}

int movingWindow(int ym0, int N){
	return (ym0 - (squared_old / N) + (squared_new / N));
}

int filter(int value){
	x[GLOBAL_COUNT % MAX_X] = value;							//INCOMING VALUE
	low[GLOBAL_COUNT % MAX_LOW] = lowPassFilter(x, low);		//LOW PASS FILTER
	high[GLOBAL_COUNT % MAX_HIGH] = highPassFilter(low, high);	//HIGH PASS FILTER
	der[GLOBAL_COUNT % MAX_DER] = derivativeFilter(high);		//DERIVATIVE FILTER
	sqr[GLOBAL_COUNT % MAX_SQR] = squaredFilter(der, sqr);		//SQUARED FILTER
	mwi = movingWindow(mwi, 30);								//MOVING WINDOW INTEGRATION;
	
	/*
	run_Test((Test*)&TEST_LOW, "../Testfiles/x_low.txt", low[GLOBAL_COUNT % MAX_LOW]); //TEST LOW-PASS FILTER
	run_Test((Test*)&TEST_HIGH, "../Testfiles/x_high.txt", high[GLOBAL_COUNT % MAX_HIGH]); //TEST HIGH-PASS FILTER
	run_Test((Test*)&TEST_DER, "../Testfiles/x_der.txt", der[GLOBAL_COUNT % MAX_DER]); //TEST DERIVATIVE
	run_Test((Test*)&TEST_SQR, "../Testfiles/x_sqr.txt", sqr[GLOBAL_COUNT % MAX_SQR]); //TEST SQUARE FUNCTION
	run_Test((Test*)&TEST_MWI, "../Testfiles/x_mwi_div_pre.txt", mwi); //TEST MOWING WINDOW INTEGRATION
	*/

	return mwi;
}