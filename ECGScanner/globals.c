#include "globals.h"

Globals globals;

int GLOBAL_COUNT = 0;

int global_count(void){
	//RESET VALUE WHEN COUNTER EQUALS MAX VALUES COMMON DIVISOR
	return (GLOBAL_COUNT >= (MAX_X * MAX_Y_LOW * MAX_Y_HIGH * MAX_Y_DER * MAX_Y_SQR - 1)) ? 0 : GLOBAL_COUNT++;
}