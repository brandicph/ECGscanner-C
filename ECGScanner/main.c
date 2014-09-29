#include <stdio.h>
#include "globals.h"
#include "sensor.h"
#include "filter.h"
#include "utils.h"
#include "test.h"

//Main program
int main(void)
{
	//Loop that holds program alive
	//as long as the sensor is getting data
	while (GLOBAL_SENSOR_ACTIVE){
		
		//Next value from the sensor
		int next = getNextData();
		//Data after filtering
		int filteret = filter(next);
		//Detection function - returns 1 if Rpeak detected
		int detected = detection(filteret);

		//Increment global count variable
		global_count();
	}

	if (GLOBAL_TEST) testResults(); //Print test results
	
	return 0;
}
