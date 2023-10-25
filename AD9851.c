/*
Author: Eyobed A.
Institiution: INSA, 2016
License: GPL v3.0+
Brief: header files
*/

#include "AD9850.h"

void AD9850::InitSerial(int W_CLK, int FQ_UD, int RESET, int DATA) {
_W_CLK = W_CLK;
_FQ_UD = FQ_UD;
_RESET = RESET;
_DATA = DATA;

pinMode(_W_CLK, OUTPUT);
pinMode(_FQ_UD, OUTPUT);
pinMode(_RESET, OUTPUT);
pinMode(_DATA, OUTPUT);

digitalWrite(_RESET, LOW);
digitalWrite(_W_CLK, LOW);

serialMode = true;
}

void AD9850::InitParallel(int W_CLK, int FQ_UD, int RESET, volatile byte *port) {
_W_CLK = W_CLK;
_FQ_UD = FQ_UD;
_RESET = RESET;
_port = port;

pinMode(_W_CLK, OUTPUT);
pinMode(_FQ_UD, OUTPUT);
pinMode(_RESET, OUTPUT);

digitalWrite(_RESET, LOW);
digitalWrite(_W_CLK, LOW);

serialMode = false;
}

void AD9850::SetFrequency(unsigned long frequency) {
frequencyWord = (frequency * pow2_32) / DDS_CLOCK;
}

void AD9850::SetPhase(int phase) {
phaseWord = phase;
}

void AD9850::powerDown(bool power) {
powerOn = power;
}

void AD9850::LoadSerial() {
digitalWrite(_RESET, LOW);
digitalWrite(_W_CLK, LOW);

pulseHigh(_FQ_UD);

for(int i = 0; i < 32; i++) {
digitalWrite(_DATA, frequencyWord & 0x80000000);
frequencyWord <<= 1;
pulseHigh(_W_CLK);
}

for(int i = 0; i < 12; i++) {
digitalWrite(_DATA, phaseWord & 0x800);
phaseWord <<= 1;
pulseHigh(_W_CLK);
}

digitalWrite(_DATA, powerOn);
pulseHigh(_W_CLK);

digitalWrite(_RESET, HIGH);
}

void AD9850::LoadParallel() {
digitalWrite(_RESET, LOW);
digitalWrite(_W_CLK, LOW);

pulseHigh(_FQ_UD);

for(int i = 0; i < 32; i++) {
*_port = frequencyWord & 0x80000000;
frequencyWord <<= 1;
pulseHigh(_W_CLK);
}

for(int i = 0; i < 12; i++) {
*_port = phaseWord & 0x800;
phaseWord <<= 1;

pulseHigh(_W_CLK);

}

*_port = powerOn;
pulseHigh(_W_CLK);

digitalWrite(_RESET, HIGH);
}

void AD9850::Load() {
if(serialMode)
LoadSerial();
else
LoadParallel();
}

void AD9850::Reset() {
digitalWrite(_RESET, LOW);
digitalWrite(_W_CLK, LOW);
}
