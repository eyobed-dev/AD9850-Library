/*
Author: Eyobed A.
Institiution: INSA, 2016
License: GPL v3.0+
Brief: header files
*/

#ifndef AD9850_H
#define AD9850_H

#include <Arduino.h>

#define pulseHigh(pin) digitalWrite(pin, HIGH); delayMicroseconds(1); digitalWrite(pin, LOW)

class AD9850 {

public:
void InitSerial(int W_CLK, int FQ_UD, int RESET, int DATA);
void InitParallel(int W_CLK, int FQ_UD, int RESET, volatile byte *port);
void SetFrequency(unsigned long frequency);
void SetPhase(int phase);
void powerDown(bool power);
void Load();
void Reset();

private:
int _W_CLK;
int _FQ_UD;
int _RESET;
int _DATA;
volatile byte *_port;
bool serialMode = false;
bool powerOn = true;
unsigned long frequencyWord = 0x0;
int phaseWord = 0;
const uint64_t pow2_32 = 4294967296;
const long DDS_CLOCK = 125000000;
void LoadSerial();
void LoadParallel();
};

#endif
