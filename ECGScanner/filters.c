#include "filters.h"

#define MAX_X 13	//max length of incoming signal x
#define MAX_LOW 33	//max length of low-pass filtered signal
#define MAX_HIGH 5	//max length of high-pass filtered signal
#define MAX_DER 1	//max length of derivate filtered signal
#define MAX_SQR 30	//max length of squared signal

static int x[MAX_X]			= { 0 };	//values of signal x
static int low[MAX_LOW]		= { 0 };	//values of low-pass filtered signal
static int high[MAX_HIGH]	= { 0 };	//values of high-pass filtered signal
static int der[MAX_DER]		= { 0 };	//values of derivative filtered signal
static int sqr[MAX_SQR]		= { 0 };	//values of squared signal
static int mwi				= 0;		//latest value of mowing window integration

//Low-pass filter
//latex: y_n=2y_{n-1}-y_{n-2}+\frac{1}{32}\cdot(x_{n}-2x_{n-6}+x_{n-12})
int lowPassFilter(int *x, int *y){
	int ym1 = y[mod(GLOBAL_COUNT - 1, MAX_LOW)];
	int ym2 = y[mod(GLOBAL_COUNT - 2, MAX_LOW)];
	int xm0 = x[mod(GLOBAL_COUNT, MAX_X)];
	int xm6 = x[mod(GLOBAL_COUNT - 6, MAX_X)];
	int xm12 = x[mod(GLOBAL_COUNT - 12, MAX_X)];
	return (2 * ym1 - ym2 + (xm0 - 2 * xm6 + xm12) / 32);
}

//High-pass filter
//latex: y_n=y_{n-1}-\frac{x_{n}}{32}+x_{n-16}-x_{n-17}+\frac{x_{n-32}}{32}
int highPassFilter(int *x, int *y){
	int ym1 = y[mod(GLOBAL_COUNT - 1, MAX_HIGH)];
	int xm0 = x[mod(GLOBAL_COUNT, MAX_LOW)];
	int xm16 = x[mod(GLOBAL_COUNT - 16, MAX_LOW)];
	int xm17 = x[mod(GLOBAL_COUNT - 17, MAX_LOW)];
	int xm32 = x[mod(GLOBAL_COUNT - 32, MAX_LOW)];
	return (ym1 - (xm0/32) + xm16 - xm17 + (xm32/ 32));
}

//Derivative filter
//latex: y_n=\frac{1}{8}(2x_{n}+x_{n-1}-x_{n-3}-2x_{n-4})
int derivativeFilter(int *x){
	int xm0 = x[mod(GLOBAL_COUNT, MAX_HIGH)];
	int xm1 = x[mod(GLOBAL_COUNT - 1, MAX_HIGH)];
	int xm3 = x[mod(GLOBAL_COUNT - 3, MAX_HIGH)];
	int xm4 = x[mod(GLOBAL_COUNT - 4, MAX_HIGH)];
	return ((2 * xm0 + xm1 - xm3 - 2 * xm4) / 8);
}


//Squaring filter
//latex: y_n=x_{n}^{2}
//save last value before override so we can calculate the MWI at time O(c)
static int squared_old = 0;
static int squared_new = 0;
int squaredFilter(int *x, int *y){
	int xm0 = x[mod(GLOBAL_COUNT, MAX_DER)];
	squared_old = y[mod(GLOBAL_COUNT, MAX_SQR)];
	squared_new = xm0 * xm0;
	return squared_new;
}

//Mowing window integration
//latex: y_n=\frac{1}{N}(x_{n-(N-1)}+x_{n-(N-2)}+\ldots+x_{n})
int movingWindow(int ym0, int N){
	return (ym0 - (squared_old / N) + (squared_new / N));
}

//Filter function
//Gathers all the filters in one sequence
int filter(int value){
	x[GLOBAL_COUNT % MAX_X] = value;							//INCOMING VALUE
	low[GLOBAL_COUNT % MAX_LOW] = lowPassFilter(x, low);		//LOW PASS FILTER
	high[GLOBAL_COUNT % MAX_HIGH] = highPassFilter(low, high);	//HIGH PASS FILTER
	der[GLOBAL_COUNT % MAX_DER] = derivativeFilter(high);		//DERIVATIVE FILTER
	sqr[GLOBAL_COUNT % MAX_SQR] = squaredFilter(der, sqr);		//SQUARED FILTER
	mwi = movingWindow(mwi, 30);								//MOVING WINDOW INTEGRATION;
	
	if (GLOBAL_DEBUG) {
		run_TestFilter((Test*)&TEST_LOW, "LOW", "../Testfiles/x_low.txt", low[GLOBAL_COUNT % MAX_LOW]);			//TEST LOW-PASS FILTER
		run_TestFilter((Test*)&TEST_HIGH, "HIGH", "../Testfiles/x_high.txt", high[GLOBAL_COUNT % MAX_HIGH]);	//TEST HIGH-PASS FILTER
		run_TestFilter((Test*)&TEST_DER, "DER", "../Testfiles/x_der.txt", der[GLOBAL_COUNT % MAX_DER]);			//TEST DERIVATIVE
		run_TestFilter((Test*)&TEST_SQR, "SQR", "../Testfiles/x_sqr.txt", sqr[GLOBAL_COUNT % MAX_SQR]);			//TEST SQUARE FUNCTION
		run_TestFilter((Test*)&TEST_MWI, "MWI", "../Testfiles/x_mwi_div_pre.txt", mwi);							//TEST MOWING WINDOW INTEGRATION
	}

	return mwi;
}