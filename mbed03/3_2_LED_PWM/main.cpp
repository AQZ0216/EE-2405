#include "mbed.h"

PwmOut PWM1(D6);
AnalogIn Ain(A0);
int main(){
  while(1){
    PWM1.period(0.5);
    PWM1 = Ain;
    wait(0.1);
  }
}