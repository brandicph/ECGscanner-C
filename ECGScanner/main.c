#include <stdio.h>
#include "globals.h"
#include "sensor.h"
#include "filter.h"
#include "utils.h"

int main(void)
{

	while (GLOBAL_SENSOR_ACTIVE){
		
		int next = getNextData();
		int filteret = filter(next);
		int detected = detection(filteret);

		global_count();
	}
	testResults();
	return 0;
}
