#ifndef GLOBALS_H
#define GLOBALS_H

typedef struct {
	int a;
	int b;
	// ...
	int z;
} Globals;

extern Globals globals;

extern int GLOBAL_COUNT;

extern const enum {
	MAX_X = 13,
	MAX_Y_LOW = 33,
	MAX_Y_HIGH = 5,
	MAX_Y_DER = 1,
	MAX_Y_SQR = 30,
	MAX_Y_LOE = 3,
	MAX_Y_PEAK = 3000,
	MAX_RR_AVG1 = 8,
	MAX_RR_AVG2 = 8
};

extern int global_count();

#endif