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

int run_Test(Test *t, char *filename, int actual){
	if (t->file == NULL){
		t->file = fopen(filename, "r");
		t->value = 0;
		t->read = 0;
		t->errors = 0;
	}

	if (t->read = fscanf(t->file, "%i\n", &t->value) != EOF){

		if (t->value != actual)
			t->errors++;
		return t->value;
	}

	fclose(t->file);
	return 0;
}