#ifndef SENSOR_H
#define SENSOR_H

#define _CRT_SECURE_NO_DEPRECATE //keep VS from complaining about fopen error C4996
#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "utils.h"

int getNextData(); // Please implement me in Sensor.c

#endif
