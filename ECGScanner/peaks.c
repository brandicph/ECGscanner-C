#include "peaks.h"

#define MAX_X 3
#define MAX_PEAKS 100
#define MAX_RR_RECENT 8
#define MAX_RR_RECENT_OK 8

#define MAX_MISS 5
#define MIN_RPEAK 2000


//Initialize variables
static int peak = 0;	//Latest found peak
static int Rpeak = 0;	//Latest found Rpeak
static int SPKF = 4500;	//Estimated value of a Rpeak
static int NPKF = 2000;	//Estimated value of a noise peak
static int THRESHOLD1 = 2300;	//Lowest threshold of Rpeak
static int THRESHOLD2 = 1300;	//If threshold1 is too high at searchback
static int RR = 0;	//later: Latest time interval from last Rpeak
static int RR_Average1 = 150;	//later: RR_Recent[0..n]/n
static int RR_Average1_temp = 150;	//latest calculated RR_Average1
static int RR_Average2 = 160;	//later: RR_Recent_OK[0..n]/n
static int RR_Average2_temp = 160;	//latest calculated RR_Average2
static int RR_LOW = 120;	//Lowest interval of a Rpeak occurrence
static int RR_HIGH = 246;	//Highest interval of a Rpeak occurrence
static int RR_MISS = 352;	//If threshold1 if set to high
static int RR_Recent[MAX_RR_RECENT] = { 100, 100, 100, 100, 100, 100, 100, 100 }; //The 8 latest known intervals between Rpeaks
static int RR_Recent_OK[MAX_RR_RECENT_OK] = { 212, 212, 212, 212, 212, 212, 212, 212 }; //The 8 latest intervals with Rpeak higher than threshold1


static int x[MAX_X] = { 0 }; //three latest incomming values - needed for peak detection
static int PEAKS[MAX_PEAKS]; //List of all peaks

static int interval = 0;
static int peak_count = 0;
static int Rpeak_count = 0;
static int miss_count = 0;

int detection(int value){

	//CHECK FOR PEAKS
	int next = nextValue(value);
	int detected = 0;

	if (isPeak(next)){

		int peak = getPeak();
		savePeak(peak);

		if (peak > THRESHOLD1){
			//Time between peaks
			RR = calculateRR();

			if (RR_LOW < RR && RR < RR_HIGH){

				Rpeak = peak;

				if (Rpeak < MIN_RPEAK){
					printWarning("Your blood pressure critically low!");
				}
				printStatus(RR, Rpeak);

				saveRRInRR_Recent(RR);
				saveRRInRR_Recent_OK(RR);

				SPKF = (int)(0.125 * peak + 0.875 * SPKF);
				RR_Average1 = calcMovingAvg(RR_Average1, RR_Average1_temp, RR, MAX_RR_RECENT);
				RR_Average2 = calcMovingAvg(RR_Average2, RR_Average2_temp, RR, MAX_RR_RECENT_OK);

				RR_LOW = (int)(0.92 * RR_Average2);
				RR_HIGH = (int)(1.16 * RR_Average2);
				RR_MISS = (int)(1.66 * RR_Average2);

				THRESHOLD1 = (int)(NPKF + 0.25 * (SPKF - NPKF));
				THRESHOLD2 = (int)(0.5 * THRESHOLD1);

				//average temp for moving average calculation
				RR_Average1_temp = RR;
				RR_Average2_temp = RR;
				//keep track of the Rpeaks
				count_Rpeak();

				miss_count = 0;
				detected = 1;
			}
			else {
				count_miss();
				if (miss_count >= MAX_MISS){
					printWarning("You have an irregular heartbeat");
				}
				if (RR < RR_MISS){
					if (searchBack()){

						Rpeak = peak;

						if (Rpeak < MIN_RPEAK){
							printWarning("Your blood pressure critically low!");
						}

						saveRRInRR_Recent(RR);

						SPKF = (int)(0.25 * peak + 0.75 * SPKF);
						RR_Average1 = calcMovingAvg(RR_Average1, RR_Average1_temp, RR, MAX_RR_RECENT);

						RR_LOW = (int)(0.92 * RR_Average2);
						RR_HIGH = (int)(1.16 * RR_Average2);
						RR_MISS = (int)(1.66 * RR_Average2);

						THRESHOLD1 = (int)(NPKF + 0.25 * (SPKF - NPKF));
						THRESHOLD2 = (int)(0.5 * THRESHOLD1);

						//average temp for moving average calculation
						RR_Average1_temp = RR;
						//keep track of the Rpeaks
						count_Rpeak();

					}
				}
			}
		}
		else {
			//If peak < THRESHOLD1
			NPKF = (int)(0.125 * peak + 0.875 * NPKF);
			THRESHOLD1 = (int)(NPKF + 0.25 * (SPKF - NPKF));
			THRESHOLD2 = (int)(0.5 * THRESHOLD1);
		}
		count_peak();
	}
	count_interval();

	return detected;
}


void printWarning(char *message){
	if (GLOBAL_DEBUG) printf("VERBOSE - WARING: %ld %ld \t", GLOBAL_COUNT, Rpeak);
	printf("***WARNING: %s\n", message);
}

void printStatus(int RR, int Rpeak){
	int time = (GLOBAL_COUNT / GLOBAL_SAMPLE_RATE);
	float pulse = (float)(60.0 * GLOBAL_SAMPLE_RATE / RR);

	if (GLOBAL_DEBUG) printf("VERBOSE - STATUS: %ld %ld \t", GLOBAL_COUNT, Rpeak);
	if (GLOBAL_TEST) run_TestPeak((Test*)&TEST_RPEAK, "RPEAK", "../Testfiles/Rpeak.txt", GLOBAL_COUNT, Rpeak); //TEST LOW-PASS FILTER
	printf("time: %ld   \t||\tpulse: <3 %0.2f\n", time, pulse);
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

int searchBack(){
	int i = 0;
	int peak2;
	while (i < MAX_PEAKS){
		peak2 = PEAKS[mod(peak_count - i, MAX_PEAKS)];
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

void savePeak(int peak){
	PEAKS[mod(peak_count, MAX_PEAKS)] = peak;
}

int calculateRR(){
	int temp = interval;
	interval = 0;
	return temp;
}

int count_miss(){
	return miss_count++;
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

int calcMovingAvg(int latest_avg, int temp, int value, int N){
	return (latest_avg - (temp / N) + (value / N));
}