#ifndef _SENSORFUNCTIONS_H_
#define _SENSORFUNCTIONS_H_

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>

void setupSensors();
void initBMP180();
void getAlt(int altoffset);
const float * readSense(int GyXoff,int GyYoff, int GyZoff, int AcXoff, int AcYoff, int AcZoff);

#endif // _QUATERNIONFILTERS_H_

