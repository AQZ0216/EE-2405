#include "mbed.h"

Serial pc( USBTX, USBRX );
AnalogOut Aout(DAC0_OUT);
AnalogIn Ain(A0);

int sample = 128;
int i;

float ADCdata[128];

int main(){
  for (i = 0; i < sample; i++){
    Aout = Ain;
    ADCdata[i] = Ain;
    wait(1./sample);
  }
  for (i = 0; i < sample; i++){
    pc.printf("%1.3f\r\n", ADCdata[i]);
    wait(0.1);
  }
}