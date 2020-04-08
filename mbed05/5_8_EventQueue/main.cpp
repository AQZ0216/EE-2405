#include "mbed.h"

int main() {
    // creates a queue with the default size
    EventQueue queue;

    // events are simple callbacks
    queue.call(printf, "called immediately\r\n");
    queue.call_in(2000, printf, "called in 2 seconds\r\n");
    queue.call_every(1000, printf, "called every 1 seconds\r\n");

    // events are executed by the dispatch method
    queue.dispatch();
}