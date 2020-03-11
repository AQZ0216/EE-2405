#include "mbed.h"

DigitalOut redLED(LED1);
DigitalOut greenLED(LED2);

int main(){
  while(1){
    redLED = 1;
    greenLED = 0;
    wait(0.2);
    redLED = 0;
    greenLED = 1;
    wait(0.2);
  }
}