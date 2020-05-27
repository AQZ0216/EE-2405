#include "mbed.h"

RawSerial pc(USBTX, USBRX);
RawSerial xbee(D12, D11);

EventQueue queue(32 * EVENTS_EVENT_SIZE);
Thread t;

void pc_rx_interrupt(void);
void pc_rx(void);
void xbee_rx_interrupt(void);
void xbee_rx(void);

int main()
{
  pc.baud(9600);
  xbee.baud(9600);
  pc.printf("Begin test\r\n");
  t.start(callback(&queue, &EventQueue::dispatch_forever));

  // Setup a serial interrupt function of receiving data from pc
  pc.attach(pc_rx_interrupt, Serial::RxIrq);
  // Setup a serial interrupt function of receiving data from xbee
  xbee.attach(xbee_rx_interrupt, Serial::RxIrq);
}

void pc_rx_interrupt(void)
{
  pc.attach(NULL, Serial::RxIrq); // detach interrupt
  queue.call(&pc_rx);
}

void pc_rx(void)
{
  static int i = 0;
  static char str[50] = {0};
  while(pc.readable()){
    char c = pc.getc();
    if(c!='\r' && c!='\n'){
      pc.putc(c);
      str[i] = c;
      i++;
      str[i] = '\0';
      if(strncmp(str, "+++", 3) == 0){
        xbee.printf("+++");
        i = 0;
      }
    }else{
      i = 0;
      xbee.printf("%s\r\n", str);
      pc.printf("\r\n", str);
    }
  }
  wait(0.001);
  pc.attach(pc_rx_interrupt, Serial::RxIrq); // reattach interrupt
}

void xbee_rx_interrupt(void)
{
  xbee.attach(NULL, Serial::RxIrq); // detach interrupt
  queue.call(&xbee_rx);
}

void xbee_rx(void)
{
  while(xbee.readable()){
    char c = xbee.getc();
    if(c!='\r' && c!='\n'){
      pc.printf("%c",c);
    }else{
      pc.printf("\r\n");
    }
  }
  wait(0.001);
  xbee.attach(xbee_rx_interrupt, Serial::RxIrq); // reattach interrupt
}