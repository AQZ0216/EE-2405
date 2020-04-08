#include "mbed.h"

DigitalIn button0(SW2);
DigitalIn button1(SW3);

DigitalOut red_led(LED1);
DigitalOut green_led(LED2);

Thread thread1;
Thread thread2;

Serial pc(USBTX, USBRX); // tx, rx
Serial device1(D12, D11);  // tx, rx
Serial device2(D1, D0);  // tx, rx

char recv_from_pc;
char recv_from_k66f;

void master_thread() {
  while(1) {
    if(pc.readable()) {
      recv_from_pc = pc.getc();
      device1.putc(recv_from_pc);
    }
    else {
      device1.putc('0');
    }
    wait(0.05);
  }
}

void slave_thread() {
  red_led = 1;
  green_led = 1;
  while(1) {
    if(device2.readable()) {
      recv_from_k66f = device2.getc();
      if(recv_from_k66f == '1'){
          red_led = 1;
          green_led = 0;
      }
      else if(recv_from_k66f == '2') {
          red_led = 0;
          green_led = 1;
      }
      else {
          red_led = 1;
          green_led =1;
      }
      pc.putc(recv_from_k66f);
    }
  }
}

int main() {
  thread1.start(master_thread);
  thread2.start(slave_thread);
}