#include "utils.h"

//Modulus function
//Hack to calculate modulus of negative numbers
//This function will calculate the remainder
//if it is negative it will return the actual positive remainder
int mod(int a, int b){
	int r = a % b;
	return r < 0 ? r + b : r;
}
