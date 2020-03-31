#include "mbed.h"

Serial pc( USBTX, USBRX );
DigitalIn  Switch(SW3);
DigitalOut redLED(LED1);
DigitalOut greenLED(LED2);
AnalogIn Ain(A0);
AnalogOut Aout(DAC0_OUT);
BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);

char table[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

int sample = 1000;
int freq = 0;

float ADCdata[1000];

int main(){
  for (int i = 0; i < sample; i++){
    Aout = Ain;
    ADCdata[i] = Ain;
    wait(1./sample);
  }

  for (int i = 1; i < sample-1; i++){
    if(ADCdata[i] > ADCdata[i-1] && ADCdata[i] > ADCdata[i+1]){
        freq++;
    }
  }

  for (int i = 0; i < sample; i++){
    pc.printf("%1.3f\r\n", ADCdata[i]);
    wait(0.1);
  }

  while(1){
    if(Switch == 0){
      greenLED = 1;
      redLED = 0;
      display = table[freq/100];
      wait(1);
      display = table[(freq%100)/10];
      wait(1);
      display = table[freq%10] | 0x80;
      wait(1);
    }else{
      redLED = 1;
      greenLED = 0;
      display = 0x00;
    }
    for(float i=0; i<2; i+=0.05 ){
        Aout = 0.5 + 0.5*sin(i*3.14159);
        wait(1./freq/40);
      }
  }
}