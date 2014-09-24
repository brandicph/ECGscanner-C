#include <stdio.h>
#include "globals.h"
#include "sensor.h"
#include "utils.h"

int main(void)
{

	//unsigned long int a = 0;
	//unsigned long int b = 2;

	//printf("%d", (a - b) % 10);

	while (GLOBAL_SENSOR_ACTIVE){
		
		int next = getNextData();
		int filteret = filter(next);
		int detected = detection(filteret);

		global_count();
	}
	return 0;
}
