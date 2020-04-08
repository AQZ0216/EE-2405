#include "mbed.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
Thread thread1;
Thread thread2;

void led1_thread() {
    while (true) {
        led1 = !led1;
        wait(0.5);
    }
}

void led2_thread() {
    while (true) {
        led2 = !led2;
        wait(1);
    }
}

int main() {
    thread1.start(led1_thread);
    thread2.start(led2_thread);
}