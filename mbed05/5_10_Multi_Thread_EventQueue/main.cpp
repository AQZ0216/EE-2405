#include "mbed.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
InterruptIn sw2(SW2);
InterruptIn sw3(SW3);
EventQueue queue1(32 * EVENTS_EVENT_SIZE);
EventQueue queue2(32 * EVENTS_EVENT_SIZE);
Thread thread1;
Thread thread2;

void led1_thread()  {
    led1 = !led1;
    printf("led1 is triggered! \r\n");
}

void led2_thread()  {
    led2 = !led2;
    printf("led2 is triggered! \r\n");
}

int main() {
    thread1.start(callback(&queue1, &EventQueue::dispatch_forever));
    thread2.start(callback(&queue2, &EventQueue::dispatch_forever));

    // 'led1_thread' will execute in context of thread 'thread1'
    sw2.rise(queue1.event(led1_thread));
    // 'led2_thread' will execute in context of thread 'thread2'
    sw3.rise(queue2.event(led2_thread));
}