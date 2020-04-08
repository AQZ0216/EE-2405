#include "mbed.h"

Timer debounce;
InterruptIn button(SW2);
DigitalOut redLED(LED1);

void toggle(){
    if(debounce.read_ms()>1000){
        redLED = !redLED;
        debounce.reset();
    }
}

int main(){
    debounce.start();
    button.rise(&toggle);
    while(1);
}