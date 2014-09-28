#include "globals.h"

//Debug switch
//1 = debug || 0 = off
int GLOBAL_DEBUG = 1;

//Global variables
unsigned long int GLOBAL_COUNT = 0;
int GLOBAL_SAMPLE_RATE = 250;
int GLOBAL_SENSOR_ACTIVE = 1;
char GLOBAL_SENSOR_INPUT[] = "../Testfiles/ECG.txt";

//Global counter
unsigned long int global_count(void){
	return GLOBAL_COUNT++;
}