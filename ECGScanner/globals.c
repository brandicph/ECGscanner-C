#include "globals.h"

Globals globals;

int GLOBAL_COUNT = 0;

int SAMPLE_RATE = 250; //(sampling rate is 250 samples pr. second (250 Hz)

#define MAX_X 13
#define MAX_LOW 33
#define MAX_HIGH 5
#define MAX_DER 1
#define MAX_SQR 30

int global_count(void){
	//RESET VALUE WHEN COUNTER EQUALS MAX VALUES COMMON DIVISOR
	return (GLOBAL_COUNT >= (MAX_X * MAX_LOW * MAX_HIGH * MAX_DER * MAX_SQR - 1)) ? 0 : GLOBAL_COUNT++;
}