#ifndef SENSOR_H
#define SENSOR_H

#define _CRT_SECURE_NO_DEPRECATE //keep VS from complaining about fopen error C4996

//includes
#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "utils.h"

//public prototypes
int getNextData();

#endif
