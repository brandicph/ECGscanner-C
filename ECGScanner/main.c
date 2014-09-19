#include <stdio.h>
#include "sensor.h"
#include "utils.h"


struct Peak {
	int value;
	int count;
};

int main()
{
	static const enum {
		MAX_X = 13,
		MAX_Y_LOW = 33,
		MAX_Y_HIGH = 5,
		MAX_Y_DER = 1,
		MAX_Y_SQR = 30,
		MAX_Y_LOE = 3,
		MAX_Y_PEAK = 3000
	};

	static const enum {
		MAX_RR_AVG1 = 8,
		MAX_RR_AVG2 = 8
	};

	int x[MAX_X] = { 0 };
	int y_low[MAX_Y_LOW] = { 0 };
	int y_high[MAX_Y_HIGH] = { 0 };
	int y_der[MAX_Y_DER] = { 0 };
	int y_sqr[MAX_Y_SQR] = { 0 };
	int y_loe[MAX_Y_LOE] = { 0 };
	int y_peak[MAX_Y_PEAK] = { 0 };

	int RR_avg1[MAX_RR_AVG1] = { 0 };
	int RR_avg2[MAX_RR_AVG2] = { 0 };


	int y_mwi = 0;

	int i;
	int count = 0;
	int time = 0;

	int peak_count = 0;
	int threshold_count = 0;

	struct Peak *p = NULL;

	//Estimated value - further explanation in the report
	int SPKF = 4500;
	int NPKF = 2000;
	int THRESHOLD1 = 0;
	int THRESHOLD2 = 0;
	int RR_AVERAGE1 = 0;
	int RR_AVERAGE2 = 0;

	int RR_AVG1_TEMP = 0;
	int RR_AVG2_TEMP = 0;

	struct Peak peaks[MAX_Y_PEAK];

	for (i = 0; i < 10000; i++){
		int next = getNextData();
		//RAW -> X
		x[count % MAX_X] = next;

		//LOW PASS FILTER
		int y0_low = lowPassFilter(
			y_low[mod(count - 1, MAX_Y_LOW)],
			y_low[mod(count - 2, MAX_Y_LOW)],
			x[mod(count, MAX_X)],
			x[mod(count - 6, MAX_X)],
			x[mod(count - 12, MAX_X)]
			);
		y_low[count % MAX_Y_LOW] = y0_low;

		//HIGH PASS FILTER
		int y0_high = highPassFilter(
			y_high[mod(count - 1, MAX_Y_HIGH)],
			y_low[mod(count, MAX_Y_LOW)],
			y_low[mod(count - 16, MAX_Y_LOW)],
			y_low[mod(count - 17, MAX_Y_LOW)],
			y_low[mod(count - 32, MAX_Y_LOW)]
			);
		y_high[count % MAX_Y_HIGH] = y0_high;

		//DERIVATIVE FILTER
		int y0_der = derivativeFilter(
			y_high[mod(count, MAX_Y_HIGH)],
			y_high[mod(count - 1, MAX_Y_HIGH)],
			y_high[mod(count - 3, MAX_Y_HIGH)],
			y_high[mod(count - 4, MAX_Y_HIGH)]
			);
		y_der[count % MAX_Y_DER] = y0_der;

		//SQUARED FILTER
		int y0_sqr = squaredFilter(y_der[mod(count, MAX_Y_DER)]);

		//save last value before override so we can calculate the mean O(c)
		int temp = y_sqr[count % MAX_Y_SQR];
		y_sqr[count % MAX_Y_SQR] = y0_sqr;

		//MOVING WINDOW INTEGRATION
		y_mwi = movingWindow(y_mwi, temp, y0_sqr, 30);

		y_loe[count % MAX_Y_LOE] = y_mwi;

		int y0_loe = peakDetection(
			y_loe[mod(count - 1, MAX_Y_LOE)],
			y_loe[mod(count, MAX_Y_LOE)],
			y_loe[mod(count + 1, MAX_Y_LOE)]
			);


		printf("LOW: %d\n", y0_low);
		printf("HIGH: %d\n", y0_high);
		printf("DER: %d\n", y0_der);
		printf("SQR: %d\n", y0_sqr);
		printf("MWI: %d\n", y_mwi);
		printf("\n");















		if (y0_loe){

			int peak = y_mwi;

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

		//RESET VALUE WHEN COUNTER EQUALS MAX VALUES COMMON DIVISOR
		count = (count >= (MAX_X * MAX_Y_LOW * MAX_Y_HIGH * MAX_Y_DER * MAX_Y_SQR - 1)) ? 0 : count + 1;

	}

	return 0;
}
