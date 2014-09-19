#include <stdio.h>
#include "globals.h"
#include "sensor.h"
#include "utils.h"

int main()
{

	int i;

	for (i = 0; i < 10000; i++){
		
		int next = getNextData();
		int filteret = filter(next);
		int detected = detection(filteret);

		global_count();

	}

	return 0;
}
