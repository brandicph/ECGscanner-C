#include "sensor.h"

static const char filename[] = "ECG.txt";
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

int lowPassFilter(int ym1, int ym2, int xm0, int xm6, int xm12){
	return (2*ym1 - ym2 + (xm0 - 2*xm6 + xm12)/32);
}

int highPassFilter(int ym0, int xm0, int xm16, int xm17, int xm32){
	return (ym0 + xm16 - xm17 + ((xm32 - xm0)/32));
}

int derivativeFilter(int xm0, int xm1, int xm3, int xm4){
	return ((2*xm0 + xm1 - xm3 - 2*xm4)/8);
}

int squaredFilter(int xm0){
	return xm0 * xm0;
}

int movingWindow(int ym0, int xold, int xnew, int N){
	return (ym0 - (xold/N) + (xnew/N));
}

int movAvg(int ym0, int xold, int xnew, int N){
	return movingWindow(ym0, xold, xnew, N);
}

int peakDetection(int xm1, int x, int xp1){
	if (xm1 < x && x > xp1)
		return 1;
	return 0;
}


