#include "mbed.h"

AnalogOut Aout(DAC0_OUT);
int main(){
  while(1){
    Aout = 0.25;  // 0.25 * 3.3 = 0.825 v
    wait(2);
    Aout = 0.5;   // 0.50 * 3.3 = 1.650 v
    wait(2);
    Aout = 0.75;  // 0.75 * 3.3 = 2.475 v
    wait(2);
  }
}