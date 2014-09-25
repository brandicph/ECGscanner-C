#include "test.h"

static FILE *file;
static int ERRORS = 0;

Test TEST_LOW	= { .file = NULL, .value = 0, .read = 0, .errors = -1 };
Test TEST_HIGH	= { .file = NULL, .value = 0, .read = 0, .errors = -1 };
Test TEST_DER	= { .file = NULL, .value = 0, .read = 0, .errors = -1 };
Test TEST_SQR	= { .file = NULL, .value = 0, .read = 0, .errors = -1 };
Test TEST_MWI	= { .file = NULL, .value = 0, .read = 0, .errors = -1 };

int getNextData(char *filename){
	int value, read;

	if (!file)
		file = fopen(filename, "r");

	if (read = fscanf(file, "%d", &value) != EOF)
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

void testResults(){
	int total = TEST_LOW.errors + TEST_HIGH.errors + TEST_DER.errors + TEST_SQR.errors + TEST_MWI.errors;
	printf("\n\n====== Test results - errors\n", "");
	printf("LOW:\t %d\n", TEST_LOW.errors);
	printf("HIGH:\t %d\n", TEST_HIGH.errors);
	printf("DER:\t %d\n", TEST_DER.errors);
	printf("SQR:\t %d\n", TEST_SQR.errors);
	printf("MWI:\t %d\n", TEST_MWI.errors);
	printf("---------\n", "");
	printf("TOTAL:\t %d\n", total);
	printf("============================\n\n", "");
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