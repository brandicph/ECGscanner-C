#include "test.h"

static FILE *file;
static int ERRORS = 0;

Test TEST_LOW = { .file = NULL, .value1 = 0, .value2 = 0, .read = 0, .errors = -1 };
Test TEST_HIGH = { .file = NULL, .value1 = 0, .value2 = 0, .read = 0, .errors = -1 };
Test TEST_DER = { .file = NULL, .value1 = 0, .value2 = 0, .read = 0, .errors = -1 };
Test TEST_SQR = { .file = NULL, .value1 = 0, .value2 = 0, .read = 0, .errors = -1 };
Test TEST_MWI = { .file = NULL, .value1 = 0, .value2 = 0, .read = 0, .errors = -1 };
Test TEST_RPEAK = { .file = NULL, .value1 = 0, .value2 = 0, .read = 0, .errors = -1 };

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
	int total = TEST_LOW.errors + TEST_HIGH.errors + TEST_DER.errors + TEST_SQR.errors + TEST_MWI.errors + TEST_RPEAK.errors;
	printf("\n\n====== Test results - errors\n", "");
	printf("LOW:\t %d\n", TEST_LOW.errors);
	printf("HIGH:\t %d\n", TEST_HIGH.errors);
	printf("DER:\t %d\n", TEST_DER.errors);
	printf("SQR:\t %d\n", TEST_SQR.errors);
	printf("MWI:\t %d\n", TEST_MWI.errors);
	printf("RPEAK:\t %d\n", TEST_RPEAK.errors);
	printf("---------\n", "");
	printf("TOTAL:\t %d\n", total);
	printf("============================\n\n", "");
}

void init_Test(Test *t, char *filename){
	if (t->file == NULL){
		t->file = fopen(filename, "r");
		t->value1 = 0;
		t->value2 = 0;
		t->read = 0;
		t->errors = 0;
	}
}

void run_TestPeak(Test *t, char *filename, int actual1, int actual2){
	init_Test(t, filename);
	if (t->read = fscanf(t->file, "%d %d", &t->value1, &t->value2) != EOF)
		if (t->value1 != actual1 && t->value2 != actual2)
			t->errors++;

	if (!t->read) fclose(t->file);
}

void run_TestFilter(Test *t, char *filename, int actual){
	init_Test(t, filename);
	if (t->read = fscanf(t->file, "%d", &t->value1) != EOF)
		if (t->value1 != actual)
			t->errors++;

	if(!t->read) fclose(t->file);
}