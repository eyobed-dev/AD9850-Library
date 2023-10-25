# AD9850-library



## Intro

This is a library class implementing the functionalities of AD9850 125MHz DDS synthesizer. It supports configuring the chip in serial or parallel mode during runtime. The chip is similar to the AD9851 with the latter supporting upto 180MHz

## Usage

Download the zip file from releases section and add it to the IDE

In your code, create an object that represents the DDS.

```
AD9851 ad9851;
```
To use serial data loading define your pins and use smething like

```
ad9851.InitSerial(W_CLK,FQ_UD,RESET,DATA);
```
NOTE: if your project does not use parallel loading you must tie D0 and D1 to 5V through a 10kOhm resistor. otherwise you have to initialize parallel loading first.

To use parallel loading define a port (Ex. PORTD), the other pins and use 

```
ad9851.InitParallel(W_CLK,FQ_UD,RESET,&port)
```
The following member functions are available for usage

     SetFrequency(unsigned long frequency);
     SetPhase(int phase);
     EnablePLL(bool pll);
     powerDown(bool power);
     Load();
     Reset();

NB:Run Load after setting frequency and phase.
