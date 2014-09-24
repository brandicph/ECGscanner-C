#include "sensor.h"

static FILE *file;

int getNextData(){
	int value;

	if (file == NULL)
		file = fopen(GLOBAL_SENSOR_INPUT, "r");

	if (GLOBAL_SENSOR_ACTIVE = fscanf(file, "%i\n", &value) != EOF)
		return value;

	fclose(file);
	return 0;
}


