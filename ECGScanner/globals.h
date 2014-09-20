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

extern int global_count();

#endif