#include "globals.h"

unsigned long int GLOBAL_COUNT = 0;
int GLOBAL_SAMPLE_RATE = 250;
int GLOBAL_SENSOR_ACTIVE = 1;
char GLOBAL_SENSOR_INPUT[] = "../Testfiles/ECG.txt";

static int MAX_COUNT = 64350; //MAX_X * MAX_LOW * MAX_HIGH * MAX_DER * MAX_SQR

int global_count(void){
	//RESET VALUE WHEN COUNTER EQUALS MAX VALUES COMMON DIVISOR
	//return (GLOBAL_COUNT >= (MAX_COUNT)) ? 0 : GLOBAL_COUNT++;
	return GLOBAL_COUNT++;
}