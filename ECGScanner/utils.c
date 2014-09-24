// utils.c : includes all the extra functions need overall

//TODO: Store additional headers in UTILS.H and not in this file
//as specified in the region comment
#include "utils.h"

int mod(int a, int b)
{
   if(b < 0)
	 return mod(-a, -b);
   int ret = a % b;
   if(ret < 0)
	 ret+=b;
   return ret;
}

/*
void queue(int *queue, int arrSize, int item)
{
	int i;
	for (i = arrSize-1; i >= 0; i--){
		//printf("queue: %d\n", i);
		if (i == 0)
			queue[i] = item;
		else
			queue[i] = queue[i-1];
	}
}
*/
