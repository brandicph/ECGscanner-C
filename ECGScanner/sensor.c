#include "sensor.h"

static const char filename[] = "../Testfiles/ECG.txt";
static FILE *file;

int getNextData(){
	int value, read;

	if (file == NULL)
		file = fopen (filename, "r");

	if (read = fscanf(file, "%i\n", &value) != EOF)
		return value;

	if(!read) fclose(file);
	return 0;
}


