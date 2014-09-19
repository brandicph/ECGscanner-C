// utils.c : includes all the extra functions need overall

//TODO: Store additional headers in UTILS.H and not in this file
//as specified in the region comment
#pragma region Headers
#include "utils.h"
#pragma endregion Reference any additional headers you need in UTILS.H and not in this file


#pragma region Static variables

#pragma endregion Private variables regarding UTILS.C


#pragma region Extern variables

#pragma endregion Public variables regarding UTILS.C


#pragma region Private structures

#pragma endregion Private structures regarding UTILS.C


#pragma region Static methods

static void utilsTest()
{
	printf("Method not accessable from other files");
}

#pragma endregion Private methods regarding UTILS.C


#pragma region Extern methods

void readObject(MyStruct ms){
	printf("Value: %d", ms.i);
}

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


extern int mod(int a, int b)
{
   if(b < 0) //you can check for b == 0 separately and do what you want
	 return mod(-a, -b);
   int ret = a % b;
   if(ret < 0)
	 ret+=b;
   return ret;
}

#pragma endregion Public methods regarding UTILS.C
