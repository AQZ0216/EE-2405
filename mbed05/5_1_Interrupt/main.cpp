#include "mbed.h"

InterruptIn button(SW2);
DigitalOut led(LED1);

void ISR1(){
    led = !led;
}

int main(){
        button.rise(&ISR1);
        while(1){
        }
}