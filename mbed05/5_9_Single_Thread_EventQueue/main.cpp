#include "mbed.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
InterruptIn sw2(SW2);
InterruptIn sw3(SW3);
EventQueue queue(32 * EVENTS_EVENT_SIZE);
Thread t;

void led1_info() {
    printf("led1 is triggered! \r\n");
}

void Trig_led1()  {
    // Execute the time critical part first
    led1 = !led1;
    // The rest can execute later in user context
    queue.call(led1_info);
}

void Trig_led2()  {
    led2 = !led2;
    // Safe to use 'printf' in context of thread 't', while IRQ is not.
    printf("led2 is triggered! \r\n");
}

int main() {
    // t is a thread to process tasks in an EventQueue
    // t call queue.dispatch_forever() to start the scheduler of the EventQueue
    t.start(callback(&queue, &EventQueue::dispatch_forever));
    // 'Trig_led1' will execute in IRQ context
    sw2.rise(Trig_led1);
    // 'Trig_led2' will execute in context of thread 't'
    // 'Trig_led2' is directly put into the queue
    sw3.rise(queue.event(Trig_led2));
}