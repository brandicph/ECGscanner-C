#include "test.h"

static FILE *file;
static int ERRORS = 0;

int getNextData(char *filename){
	int value, read;

	if (file == NULL)
		file = fopen(filename, "r");

	if (read = fscanf(file, "%i\n", &value) != EOF)
		return value;

	if (!read) fclose(file);
	return 0;
}


void testData(char *filename, int actual){
	int expected = getNextData(filename);

	if (expected != actual){
		printf("%d : %d\t != %d\n", GLOBAL_COUNT + 1, actual, expected);
		ERRORS++;
	}
}