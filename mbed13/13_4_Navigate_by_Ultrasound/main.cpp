#include "mbed.h"
 #include "bbcar.h"

 DigitalOut led1(LED1);
 PwmOut pin9(D9), pin8(D8);
 DigitalInOut pin10(D10);
 Ticker servo_ticker;

 BBCar car(pin8, pin9, servo_ticker);

 int main() {
     parallax_ping  ping1(pin10);

     car.goStraight(100);
     while(1){
         if((float)ping1>10) led1 = 1;
         else{
             led1 = 0;
             car.stop();
             break;
         }
         wait(.01);
     }
 }