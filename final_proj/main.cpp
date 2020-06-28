#include "mbed.h"
#include "bbcar.h"

DigitalOut led1(LED1);
PwmOut pin13(D13), pin10(D10);
DigitalIn pin3(D3);
DigitalInOut pin9(D9);
Ticker servo_ticker;
Ticker encoder_ticker;
// RawSerial pc(USBTX, USBRX);
RawSerial xbee(D12, D11);
Serial pc(USBTX,USBRX); //tx,rx
Serial uart(D1,D0); //tx,rx

BBCar car(pin10, pin13, servo_ticker);
EventQueue queue(32 * EVENTS_EVENT_SIZE);
// EventQueue xbee_queue(32 * EVENTS_EVENT_SIZE);
Thread thr;
// Thread xbee_thread;

void xbee_rx_interrupt(void);
void xbee_rx(void);
void reply_messange(char *xbee_reply, char *messange);
void check_addr(char *xbee_reply, char *messenger);

// void log(void){

// }

int main(){
    char recv;

    pc.baud(9600);

    char xbee_reply[4];

    // XBee setting
    xbee.baud(9600);
    xbee.printf("+++");
    xbee_reply[0] = xbee.getc();
    xbee_reply[1] = xbee.getc();
    if(xbee_reply[0] == 'O' && xbee_reply[1] == 'K'){
        pc.printf("enter AT mode.\r\n");
        xbee_reply[0] = '\0';
        xbee_reply[1] = '\0';
    }
    xbee.printf("ATMY 0x212\r\n");
    reply_messange(xbee_reply, "setting MY : 0x212");

    xbee.printf("ATDL 0x112\r\n");
    reply_messange(xbee_reply, "setting DL : 0x112");

    xbee.printf("ATID 0x1\r\n");
    reply_messange(xbee_reply, "setting PAN ID : 0x1");

    xbee.printf("ATWR\r\n");
    reply_messange(xbee_reply, "write config");

    xbee.printf("ATMY\r\n");
    check_addr(xbee_reply, "MY");

    xbee.printf("ATDL\r\n");
    check_addr(xbee_reply, "DL");

    xbee.printf("ATCN\r\n");
    reply_messange(xbee_reply, "exit AT mode");
    xbee.getc();

    // start
    pc.printf("start\r\n");

    // Setup a serial interrupt function of receiving data from xbee
    thr.start(callback(&queue, &EventQueue::dispatch_forever));
    // xbee_thread.start(callback(&xbee_queue, &EventQueue::dispatch_forever));
    xbee.attach(xbee_rx_interrupt, Serial::RxIrq);

    // xbee_queue.call_every(1000, log);

    parallax_encoder encoder0(pin3, encoder_ticker);
    parallax_ping ping1(pin9);

    pc.printf("goStraight\r\n");
    encoder0.reset();
    car.goStraight(200);
    while(encoder0.get_cm()<120) wait_ms(50);
    car.stop();
    wait(0.5);

    // pc.printf("datamatrix\r\n");
    // char s1[1];
    // sprintf(s1,"datamatrix");
    // uart.puts(s1);
    // pc.printf("send\r\n");
    // wait(0.5);

    // while(1) {
    //   if(uart.readable()){
    //     recv = uart.getc();
    //     pc.putc(recv);
    //   }
    // }

    pc.printf("turnLeft\r\n");
    car.turn(200, 0.2);
    wait(1.9);
    car.stop();
    wait(0.5);

    pc.printf("goStraight\r\n");
    encoder0.reset();
    car.goStraight(200);
    while(encoder0.get_cm()<33) wait_ms(50);
    car.stop();
    wait(0.5);

    pc.printf("backwardTurnLeft\r\n");
    car.turn(-180, 0.01);
    wait(1.15);
    car.stop();
    wait(0.5);

    pc.printf("back\r\n");
    encoder0.reset();
    car.goStraight(-200);
    while(encoder0.get_cm()<30) wait_ms(50);
    car.stop();
    wait(0.5);

    pc.printf("imageClassification\r\n");
    char s2[21];
    sprintf(s2,"image_classification");
    uart.puts(s2);
    pc.printf("send\r\n");
    wait(0.5);

    while(1) {
      if(uart.readable()){
      recv = uart.getc();
      printf("%c\r\n", recv);
      break;
      }
    }
    
    pc.printf("goStraight\r\n");
    encoder0.reset();
    car.goStraight(200);
    while(encoder0.get_cm()<20) wait_ms(50);
    car.stop();
    wait(0.5);

    pc.printf("turnLeft\r\n");
    car.turn(200, 0.01);
    wait(1.1);
    car.stop();
    wait(0.5);

    pc.printf("goStraight\r\n");
    encoder0.reset();
    car.goStraight(200);
    while(encoder0.get_cm()<40) wait_ms(50);
    car.stop();
    wait(0.5);

    pc.printf("turnRight\r\n");
    car.turn(200, -0.01);
    wait(1.4);
    car.stop();
    wait(0.5);

    pc.printf("back\r\n");
    encoder0.reset();
    car.goStraight(-200);
    while(encoder0.get_cm()<30) wait_ms(50);
    car.stop();
    wait(0.5);

    pc.printf("goStraight\r\n");
    encoder0.reset();
    car.goStraight(200);
    while(encoder0.get_cm()<40) wait_ms(50);
    car.stop();
    wait(0.5);

    pc.printf("turnRight\r\n");
    car.turn(200, -0.01);
    wait(1.4);
    car.stop();
    wait(0.5);

    pc.printf("goStraight\r\n");
    encoder0.reset();
    car.goStraight(200);
    while(encoder0.get_cm()<50) wait_ms(50);
    car.stop();
    wait(0.5);

    pc.printf("turnRight\r\n");
    car.turn(200, -0.01);
    wait(1.4);
    car.stop();
    wait(0.5);

    pc.printf("goStraight\r\n");
    encoder0.reset();
    car.goStraight(200);
    while(encoder0.get_cm()<120) wait_ms(50);
    car.stop();
    wait(0.5);

    return 0;
}

void xbee_rx_interrupt(void)
{
  xbee.attach(NULL, Serial::RxIrq); // detach interrupt
  queue.call(&xbee_rx);
}

void xbee_rx(void)
{
  static int i = 0;
  static char buf[100] = {0};
  while(xbee.readable()){
    char c = xbee.getc();
    if(c!='\r' && c!='\n'){
      buf[i] = c;
      i++;
      buf[i] = '\0';
    }else{
      i = 0;
      pc.printf("Get: %s\r\n", buf);
      xbee.printf("%s", buf);
    }
  }
  wait(0.1);
  xbee.attach(xbee_rx_interrupt, Serial::RxIrq); // reattach interrupt
}

void reply_messange(char *xbee_reply, char *messange){
  xbee_reply[0] = xbee.getc();
  xbee_reply[1] = xbee.getc();
  xbee_reply[2] = xbee.getc();
  if(xbee_reply[1] == 'O' && xbee_reply[2] == 'K'){
    pc.printf("%s\r\n", messange);
    xbee_reply[0] = '\0';
    xbee_reply[1] = '\0';
    xbee_reply[2] = '\0';
  }
}

void check_addr(char *xbee_reply, char *messenger){
  xbee_reply[0] = xbee.getc();
  xbee_reply[1] = xbee.getc();
  xbee_reply[2] = xbee.getc();
  xbee_reply[3] = xbee.getc();
  pc.printf("%s = %c%c%c\r\n", messenger, xbee_reply[1], xbee_reply[2], xbee_reply[3]);
  xbee_reply[0] = '\0';
  xbee_reply[1] = '\0';
  xbee_reply[2] = '\0';
  xbee_reply[3] = '\0';
}

        //  char s[21];
        //  sprintf(s,"image_classification");
        //  uart.puts(s);
        //  pc.printf("send\r\n");
        //  wait(0.5);

  //  while(1) {
  //     if(uart.readable()){
  //           char recv = uart.getc();
  //           pc.putc(recv);
  //           pc.printf("\r\n");
  //     }
  //  }