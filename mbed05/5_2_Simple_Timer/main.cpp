#include "mbed.h"
Timer t;
Serial pc( USBTX, USBRX );

int main(){
    t.start();
    pc.printf("Hello from the other side\n");
    t.stop();
    pc.printf("The time taken was %f seconds\n", t.read());
}