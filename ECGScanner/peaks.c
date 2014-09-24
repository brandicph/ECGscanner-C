#include "peaks.h"

#define MAX_X 3
#define MAX_PEAKS 100
#define MAX_RR_RECENT 8
#define MAX_RR_RECENT_OK 8


//Initialize variables
static int peak				= 0;	//Latest found peak
static int Rpeak			= 0;	//Latest found Rpeak
static int SPKF				= 4500;	//Estimated value of a Rpeak
static int NPKF				= 2000;	//Estimated value of a noise peak
static int THRESHOLD1		= 2300;	//Lowest threshold of Rpeak
static int THRESHOLD2		= 1300;	//If threshold1 is too high at searchback
static int RR				= 0;	//later: Latest time interval from last Rpeak
static int RR_Average1		= 150;	//later: RR_Recent[0..n]/n
static int RR_Average1_temp = 150;	//latest calculated RR_Average1
static int RR_Average2		= 160;	//later: RR_Recent_OK[0..n]/n
static int RR_Average2_temp = 160;	//latest calculated RR_Average2
static int RR_LOW			= 120;	//Lowest interval of a Rpeak occurrence
static int RR_HIGH			= 246;	//Highest interval of a Rpeak occurrence
static int RR_MISS			= 352;	//If threshold1 if set to high
static int RR_Recent[MAX_RR_RECENT]			= { 100, 100, 100, 100, 100, 100, 100, 100 }; //The 8 latest known intervals between Rpeaks
static int RR_Recent_OK[MAX_RR_RECENT_OK]	= { 212, 212, 212, 212, 212, 212, 212, 212 }; //The 8 latest intervals with Rpeak higher than threshold1

//Estimated value - further explanation in the report

static int x[MAX_X] = { 0 }; //three latest incomming values - needed for peak detection

static int interval			= 0;
static int peak_count		= 0;
static int Rpeak_count		= 0;
static int threshold_count	= 0;

typedef struct Peak {
	int value;
	int interval;
} Peak;
static Peak *p = NULL;
static Peak PEAKS[MAX_PEAKS]; //List of all peaks

static int gl_count = 0;


int detection(int value){

	//CHECK FOR PEAKS
	int next = nextValue(value);

	if (isPeak(next)){

		int peak = getPeak();
		savePeak(peak, interval);

		if (peak > THRESHOLD1){
			//Time between peaks
			RR = calculateRR();

			if (RR_LOW < RR && RR < RR_HIGH){

				Rpeak = peak;

				saveRRInRR_Recent(RR);
				saveRRInRR_Recent_OK(RR);

				SPKF = 0.125 * peak + 0.875 * SPKF;
				RR_Average1 = calcMovingAvg(RR_Average1, RR_Average1_temp, RR, MAX_RR_RECENT);
				RR_Average2 = calcMovingAvg(RR_Average2, RR_Average2_temp, RR, MAX_RR_RECENT_OK);

				RR_LOW = 0.92 * RR_Average2;
				RR_HIGH = 1.16 * RR_Average2;
				RR_MISS = 1.66 * RR_Average2;

				THRESHOLD1 = NPKF + 0.25 * (SPKF - NPKF);
				THRESHOLD2 = 0.5 * THRESHOLD1;

				printf("%d %d\n", GLOBAL_COUNT, Rpeak);

				//average temp for moving average calculation
				RR_Average1_temp = RR;
				RR_Average2_temp = RR;
				//keep track of the Rpeaks
				count_Rpeak();

			} else {
				if (RR < RR_MISS){
					if (searchBack()){

						Rpeak = peak;

						saveRRInRR_Recent(RR);

						SPKF = 0.25 * peak + 0.75 * SPKF;
						RR_Average1 = calcMovingAvg(RR_Average1, RR_Average1_temp, RR, MAX_RR_RECENT);

						RR_LOW = 0.92 * RR_Average2;
						RR_HIGH = 1.16 * RR_Average2;
						RR_MISS = 1.66 * RR_Average2;

						THRESHOLD1 = NPKF + 0.25 * (SPKF - NPKF);
						THRESHOLD2 = 0.5 * THRESHOLD1;

						//average temp for moving average calculation
						RR_Average1_temp = RR;
						//keep track of the Rpeaks
						count_Rpeak();
					} else {
						//do nothing
						//return to start
					}

				} else {
					//do nothing
					//return to start
				}
				
			}

		} else {
			//If peak < THRESHOLD1
			NPKF = 0.125 * peak + 0.875 * NPKF;
			THRESHOLD1 = NPKF + 0.25 * (SPKF - NPKF);
			THRESHOLD2 = 0.5 * THRESHOLD1;
		}
		count_peak();
	}
	gl_count++;
	count_interval();
}


int searchBack(){
	int i = 0;
	int peak2;
	while (i < MAX_PEAKS){
		peak2 = PEAKS[mod(peak_count - i, MAX_PEAKS)].value;
		if (peak2 > THRESHOLD2)
			return 1;
		i++;
	}
	return 0;
}

int getPeak(void){
	return x[mod(GLOBAL_COUNT - 1, MAX_X)];
}

int nextValue(int value){
	x[GLOBAL_COUNT % MAX_X] = value;
	return value;
}

void saveRRInRR_Recent(int RR){
	RR_Recent[mod(Rpeak_count, MAX_RR_RECENT)] = RR;
}

void saveRRInRR_Recent_OK(int RR){
	RR_Recent_OK[mod(Rpeak_count, MAX_RR_RECENT_OK)] = RR;
}

void savePeak(int peak, int interval){
	PEAKS[mod(peak_count, MAX_PEAKS)].value = peak;
	PEAKS[mod(peak_count, MAX_PEAKS)].interval = interval;
}

int calculateRR(){
	int temp = interval;
	interval = 0;
	return temp;
}

int count_peak(){
	return peak_count++;
}

int count_Rpeak(){
	return Rpeak_count++;
}

int count_interval(){
	return interval++;
}

int isPeak(int value){
	//because we already added the newest value to the array
	//the formula need to be like "x[n-2] < x[n-1] > x" instead of "x[n-1] < x > x[n+1]"
	int xm1 = x[mod(GLOBAL_COUNT - 2, MAX_X)];
	int xm0 = x[mod(GLOBAL_COUNT - 1, MAX_X)];
	int xp1 = x[mod(GLOBAL_COUNT, MAX_X)];
	if (xm1 < xm0 && xm0 > xp1)
		return 1;
	return 0;
}

int calcMovingAvg(int latest_avg, int temp, int value, int N){
	return (latest_avg - (temp / N) + (value / N));
}