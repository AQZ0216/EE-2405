#include "mbed.h"

Ticker time_up;
DigitalOut blueLED(LED3);

void blink(){
    blueLED = !blueLED;
}

int main(){
    time_up.attach( &blink, 0.5 );
    while(1);
}