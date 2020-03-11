#include "mbed.h"

DigitalIn  Switch(SW3);
DigitalOut redLED(LED1);
DigitalOut greenLED(LED2);

int main(){
  while(1){
    if( Switch == 1 ){
      greenLED = 0;
      redLED = 1;
    }
    else{
      redLED = 0;
      greenLED = 1;
    }
  }
}