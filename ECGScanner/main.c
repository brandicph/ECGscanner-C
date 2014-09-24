#include <stdio.h>
#include "globals.h"
#include "sensor.h"
#include "utils.h"

int main(void)
{

	while (GLOBAL_SENSOR_ACTIVE){
		
		int next = getNextData();
		int filteret = filter(next);
		int detected = detection(filteret);

		global_count();
	}
	return 0;
}
