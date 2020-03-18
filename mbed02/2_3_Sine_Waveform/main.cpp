#include "mbed.h"
AnalogOut Aout(DAC0_OUT);

int main(){
  float i;
  while(1){
    for( i=0; i<2; i+=0.05 ){
      Aout = 0.5 + 0.5*sin(i*3.14159);
      wait(0.001);
    }
  }
}