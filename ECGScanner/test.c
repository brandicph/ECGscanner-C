#include "test.h"

//List of the tests to run
//Initialize the values to allocate memory
Test TEST_LOW	= { .file = NULL, .value1 = 0, .value2 = 0, .read = 0, .errors = -1 };
Test TEST_HIGH	= { .file = NULL, .value1 = 0, .value2 = 0, .read = 0, .errors = -1 };
Test TEST_DER	= { .file = NULL, .value1 = 0, .value2 = 0, .read = 0, .errors = -1 };
Test TEST_SQR	= { .file = NULL, .value1 = 0, .value2 = 0, .read = 0, .errors = -1 };
Test TEST_MWI	= { .file = NULL, .value1 = 0, .value2 = 0, .read = 0, .errors = -1 };
Test TEST_RPEAK = { .file = NULL, .value1 = 0, .value2 = 0, .read = 0, .errors = -1 };

//Test array of pointers that points to the tests
//this will be used to autogenerate the test results
static Test *tests[] = { &TEST_LOW, &TEST_HIGH, &TEST_DER, &TEST_SQR, &TEST_MWI, &TEST_RPEAK };


//Initializer to open file and add startvalues to the test
void init_Test(Test *t, char *name, char *filename){
	if (t->file == NULL){
		t->name = &name[0];
		t->file = fopen(filename, "r");
		t->value1 = 0;
		t->value2 = 0;
		t->read = 0;
		t->errors = 0;
	}
}

//Printing the final result of the tests
//Using the test declared in the Test array
void testResults(){
	printf("\n\n====== Test results - errors\n", "");

	int i;
	int total = 0;
	int length = (sizeof(tests) / sizeof(tests[0]));
	for (i = 0; i < length; i++){
		printf("%s:\t %d\n", tests[i]->name, tests[i]->errors);
		total += tests[i]->errors;
	}

	printf("---------\n", "");
	printf("TOTAL:\t %d\n", total);
	printf("============================\n\n", "");
}

//Test for Rpeak
//Reads testfile with two two values pr. line (two columns)
void run_TestPeak(Test *t, char *name, char *filename, int actual1, int actual2){
	init_Test(t, name, filename);
	if (t->read = fscanf(t->file, "%d %d", &t->value1, &t->value2) != EOF)
		if (t->value1 != actual1 && t->value2 != actual2){
			printf("TEST (%s) --> expected: %d | %d != actual: %d | %d\n", t->name,  t->value1, t->value2, actual1, actual2);
			t->errors++;
		}
	if (!t->read) fclose(t->file);
}

//Test for Filters
//Reads testfile with one value pr. line (one column)
void run_TestFilter(Test *t, char *name, char *filename, int actual){
	init_Test(t, name, filename);
	if (t->read = fscanf(t->file, "%d", &t->value1) != EOF)
		if (t->value1 != actual){
			printf("TEST (%s) --> expected: %d != actual: %d\n", t->name, t->value1, actual);
			t->errors++;
		}
	if(!t->read) fclose(t->file);
}