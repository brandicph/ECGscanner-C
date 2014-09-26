#include "sensor.h"

//Sensor interface
//This function returns the incoming data
static FILE *file;
int getNextData(){
	int value;

	if (!file)
		file = fopen(GLOBAL_SENSOR_INPUT, "r");

	if (GLOBAL_SENSOR_ACTIVE = fscanf(file, "%d", &value) != EOF)
		return value;

	fclose(file);
	return 0;
}


