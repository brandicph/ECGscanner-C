#include "filters.h"

static int x[MAX_X] = { 0 };
static int y_low[MAX_Y_LOW] = { 0 };
static int y_high[MAX_Y_HIGH] = { 0 };
static int y_der[MAX_Y_DER] = { 0 };
static int y_sqr[MAX_Y_SQR] = { 0 };
static int y_mwi = 0;

int lowPassFilter(int *x, int *y){
	int ym1 = y[mod(GLOBAL_COUNT - 1, MAX_Y_LOW)];
	int ym2 = y[mod(GLOBAL_COUNT - 2, MAX_Y_LOW)];
	int xm0 = x[mod(GLOBAL_COUNT, MAX_X)];
	int xm6 = x[mod(GLOBAL_COUNT - 6, MAX_X)];
	int xm12 = x[mod(GLOBAL_COUNT - 12, MAX_X)];
	return (2 * ym1 - ym2 + (xm0 - 2 * xm6 + xm12) / 32);
}

int highPassFilter(int *x, int *y){
	int ym0 = y[mod(GLOBAL_COUNT - 1, MAX_Y_HIGH)];
	int xm0 = x[mod(GLOBAL_COUNT, MAX_Y_LOW)];
	int xm16 = x[mod(GLOBAL_COUNT - 16, MAX_Y_LOW)];
	int xm17 = x[mod(GLOBAL_COUNT - 17, MAX_Y_LOW)];
	int xm32 = x[mod(GLOBAL_COUNT - 32, MAX_Y_LOW)];
	return (ym0 + xm16 - xm17 + ((xm32 - xm0) / 32));
}

int derivativeFilter(int *x){
	int xm0 = x[mod(GLOBAL_COUNT, MAX_Y_HIGH)];
	int xm1 = x[mod(GLOBAL_COUNT - 1, MAX_Y_HIGH)];
	int xm3 = x[mod(GLOBAL_COUNT - 3, MAX_Y_HIGH)];
	int xm4 = x[mod(GLOBAL_COUNT - 4, MAX_Y_HIGH)];
	return ((2 * xm0 + xm1 - xm3 - 2 * xm4) / 8);
}

//save last value before override so we can calculate the mean O(c)
static int squared_old = 0;
static int squared_new = 0;
int squaredFilter(int *x, int *y){
	int xm0 = x[mod(GLOBAL_COUNT, MAX_Y_DER)];
	squared_old = y[mod(GLOBAL_COUNT, MAX_Y_SQR)];
	squared_new = xm0 * xm0;
	return squared_new;
}

int movingWindow(int ym0, int N){
	return (ym0 - (squared_old / N) + (squared_new / N));
}

int filter(int value){
	x[GLOBAL_COUNT % MAX_X] = value;									//INCOMING VALUE
	y_low[GLOBAL_COUNT % MAX_Y_LOW] = lowPassFilter(x, y_low);			//LOW PASS FILTER
	y_high[GLOBAL_COUNT % MAX_Y_HIGH] = highPassFilter(y_low, y_high);	//HIGH PASS FILTER
	y_der[GLOBAL_COUNT % MAX_Y_DER] = derivativeFilter(y_high);			//DERIVATIVE FILTER
	y_sqr[GLOBAL_COUNT % MAX_Y_SQR] = squaredFilter(y_der, y_sqr);		//SQUARED FILTER
	y_mwi = movingWindow(y_mwi, 30);									//MOVING WINDOW INTEGRATION;

	//Just for debugging
	//printf("X: %d\n", x[GLOBAL_COUNT % MAX_X]);
	printf("LOW: %d\n", y_low[GLOBAL_COUNT % MAX_Y_LOW]);
	printf("HIGH: %d\n", y_high[GLOBAL_COUNT % MAX_Y_HIGH]);
	printf("DER: %d\n", y_der[GLOBAL_COUNT % MAX_Y_DER]);
	printf("SQR: %d\n", y_sqr[GLOBAL_COUNT % MAX_Y_SQR]);
	printf("MWI: %d\n", y_mwi);
	printf("\n", "");

	return y_mwi;
}