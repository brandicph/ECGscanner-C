#include "peaks.h"

//Estimated value - further explanation in the report
static int SPKF = 4500;
static int NPKF = 2000;
static int THRESHOLD1 = 0;
static int THRESHOLD2 = 0;
static int RR_AVERAGE1 = 0;
static int RR_AVERAGE2 = 0;
static int RR_AVG1_TEMP = 0;
static int RR_AVG2_TEMP = 0;

static int y_loe[MAX_Y_LOE] = { 0 };
static int y_peak[MAX_Y_PEAK] = { 0 };
static int RR_avg1[MAX_RR_AVG1] = { 0 };
static int RR_avg2[MAX_RR_AVG2] = { 0 };

static int time = 0;
static int peak_count = 0;
static int threshold_count = 0;

static struct Peak {
	int value;
	int count;
};
static struct Peak *p = NULL;
static struct Peak peaks[MAX_Y_PEAK];

int detection(int value){

	//CHECK FOR PEAKS
	y_loe[GLOBAL_COUNT % MAX_Y_LOE] = value;

	if (isPeak(value)){

		int peak = value;

		//Save peak in peaks
		peaks[mod(peak_count, MAX_Y_PEAK)].value = peak;
		peaks[mod(peak_count, MAX_Y_PEAK)].count = peak_count;

		RR_AVERAGE1 = movAvg(RR_AVERAGE1, RR_AVG1_TEMP, peaks[mod(peak_count, MAX_RR_AVG1)].value, MAX_RR_AVG1);

		RR_AVG1_TEMP = peaks[mod(peak_count, MAX_Y_PEAK)].value;


		if (peaks[mod(peak_count, MAX_Y_PEAK)].value > THRESHOLD1){
			//Time between peaks
			int RR = time;
			time = 0;

			RR_AVERAGE2 = movAvg(RR_AVERAGE2, RR_AVG2_TEMP, peaks[mod(peak_count, MAX_RR_AVG2)].value, MAX_RR_AVG2);
			int RR_LOW = 0.92 * RR_AVERAGE2;
			int RR_HIGH = 1.16 * RR_AVERAGE2;
			int RR_MISS = 1.66 * RR_AVERAGE2;


			if (RR_LOW < RR < RR_HIGH){
				SPKF = 0.125 * peak + 0.875 * SPKF;
				int RecentRR_OK = RR;
				int RecentRR = RR;
			}

			RR_AVG2_TEMP = peaks[mod(peak_count, MAX_Y_PEAK)].value;
			threshold_count = (threshold_count < MAX_RR_AVG2) ? threshold_count + 1 : 0;

		}
		else {
			NPKF = 0.125 * peaks[mod(peak_count, MAX_Y_PEAK)].value + 0.875 * NPKF;
			THRESHOLD1 = NPKF + 0.5 * (SPKF - NPKF);
			THRESHOLD2 = 0.5 * THRESHOLD1;
		}

		peak_count++;
	}
	time++;
}


int isPeak(int *x){
	int xm1 = y_loe[mod(GLOBAL_COUNT - 1, MAX_Y_LOE)];
	int xm0 = y_loe[mod(GLOBAL_COUNT, MAX_Y_LOE)];
	int xp1 = y_loe[mod(GLOBAL_COUNT + 1, MAX_Y_LOE)];
	if (xm1 < xm0 && xm0 > xp1)
		return 1;
	return 0;
}