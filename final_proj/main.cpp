#include "mbed.h"
#include "bbcar.h"

DigitalOut led1(LED1);
PwmOut pin13(D13), pin10(D10);
DigitalIn pin3(D3);
DigitalInOut pin9(D9);
Ticker servo_ticker;
Ticker encoder_ticker;
RawSerial xbee(D12, D11);
Serial pc(USBTX,USBRX); //tx,rx
Serial uart(D1,D0); //tx,rx

BBCar car(pin10, pin13, servo_ticker);
EventQueue queue(32 * EVENTS_EVENT_SIZE);
EventQueue xbee_queue(32 * EVENTS_EVENT_SIZE);
Thread thr;
Thread xbee_thread;

void xbee_rx_interrupt(void);
void xbee_rx(void);
void reply_messange(char *xbee_reply, char *messange);
void check_addr(char *xbee_reply, char *messenger);
void info_log(void);

char info = 'N';

int main(){
    char recv;
    float ping_mid, ping_left, ping_right;

    pc.baud(9600);

    char xbee_reply[4];

    // start
    pc.printf("start\r\n");

    // Setup a serial interrupt function of receiving data from xbee
    thr.start(callback(&queue, &EventQueue::dispatch_forever));
    xbee_thread.start(callback(&xbee_queue, &EventQueue::dispatch_forever));
    xbee.attach(xbee_rx_interrupt, Serial::RxIrq);

    xbee_queue.call_every(1000, &info_log);

    parallax_encoder encoder0(pin3, encoder_ticker);
    parallax_ping ping1(pin9);

    led1 = 1;

    // go straight
    info = 'w';
    encoder0.reset();
    car.goStraight(200);
    while(encoder0.get_cm()<120) wait_ms(50);
    car.stop();
    led1 = 0;
    wait(0.5);
    led1 = 1;

    // left
    info = 'a';
    car.turn(200, 0.2);
    wait(1.9);
    car.stop();
    led1 = 0;
    wait(0.5);
    led1 = 1;

    // M1
    // go straight
    info = 'w';
    encoder0.reset();
    car.goStraight(200);
    while(encoder0.get_cm()<30) wait_ms(50);
    car.stop();
    led1 = 0;
    wait(0.5);
    led1 = 1;

    // backward left
    info = 'z';
    car.turn(-180, 0.01);
    wait(1.3);
    car.stop();
    led1 = 0;
    wait(0.5);
    led1 = 1;

    info = 'N';
    char s2[21];
    sprintf(s2,"image_classification");
    uart.puts(s2);
    pc.printf("send\r\n");
    wait(0.5);

    while(1) {
      if(uart.readable()){
        recv = uart.getc();
        xbee.printf("%c\r\n", recv);
        break;
      }
    }
    
    led1 = 0;
    wait(0.5);
    led1 = 1;

    // left
    info = 'a';
    car.turn(200, 0.01);
    wait(1.1);
    car.stop();
    led1 = 0;
    wait(0.5);
    led1 = 1;

    // go straight
    info = 'w';
    encoder0.reset();
    car.goStraight(200);
    while(encoder0.get_cm()<37) wait_ms(50);
    car.stop();
    led1 = 0;
    wait(0.5);
    led1 = 1;

    // right
    info = 'd';
    car.turn(200, -0.01);
    wait(1.0);
    car.stop();
    led1 = 0;
    wait(0.5);
    led1 = 1;

    // back
    info = 's';
    encoder0.reset();
    car.goStraight(-200);
    while(encoder0.get_cm()<25) wait_ms(50);
    car.stop();
    led1 = 0;
    wait(0.5);
    led1 = 1;

    // go straight
    info = 'w';
    encoder0.reset();
    car.goStraight(200);
    while(encoder0.get_cm()<17) wait_ms(50);
    car.stop();
    led1 = 0;
    wait(0.5);
    led1 = 1;

    // right
    info = 'd';
    car.turn(200, -0.2);
    wait(2.15);
    car.stop();
    led1 = 0;
    wait(0.5);
    led1 = 1;

    // go straight
    info = 'w';
    encoder0.reset();
    car.goStraight(200);
    while(encoder0.get_cm()<37) wait_ms(50);
    car.stop();
    led1 = 0;
    wait(0.5);
    led1 = 1;

    // right
    info = 'd';
    car.turn(200, -0.2);
    wait(2.05);
    car.stop();
    led1 = 0;
    wait(0.5);
    led1 = 1;

    // go straight
    info = 'w';
    encoder0.reset();
    car.goStraight(200);
    while(encoder0.get_cm()<90) wait_ms(50);
    car.stop();
    led1 = 0;
    wait(0.5);
    led1 = 1;

    // right
    info = 'd';
    car.turn(200, -0.2);
    wait(1.9);
    car.stop();
    led1 = 0;
    wait(0.5);
    led1 = 1;

    // M2
    // go straight
    info = 'w';
    encoder0.reset();
    car.goStraight(200);
    while(encoder0.get_cm()<30) wait_ms(50);
    car.stop();
    led1 = 0;
    wait(0.5);
    led1 = 1;

    // right
    info = 'd';
    car.turn(200, -0.1);
    wait(1.5);
    car.stop();
    led1 = 0;
    wait(0.5);
    led1 = 1;

    // left
    info = 'a';
    car.turn(200, 0.1);
    wait(1.4);
    car.stop();
    led1 = 0;
    wait(0.5);
    led1 = 1;

    // Identify Object
    info = 'N';
    ping_mid = (float)ping1;

    car.turn(200, 0.01);
    wait(0.5);
    car.stop();
    wait(0.5);
    ping_left = (float)ping1;
    car.turn(-200, 0.01);
    wait(0.5);
    car.stop();
    wait(0.5);

    car.turn(200, -0.01);
    wait(0.5);
    car.stop();
    wait(0.5);
    ping_right = (float)ping1;
    car.turn(-200, -0.01);
    wait(0.5);
    car.stop();
    led1 = 0;
    wait(0.5);
    led1 = 1;

    if(ping_right > ping_left + 5){
      xbee.printf("2\r\n");
    }else if(ping_left < ping_mid || ping_right < ping_mid){
      xbee.printf("3\r\n");
    }else if(ping_left > ping_mid+5 || ping_right > ping_mid+5){
      xbee.printf("0\r\n");
    }else{
      xbee.printf("1\r\n");
    }

    // left
    info = 'a';
    car.turn(200, 0.2);
    wait(1.7);
    car.stop();
    led1 = 0;
    wait(0.5);
    led1 = 1;

    // right
    info = 'd';
    car.turn(200, -0.01);
    wait(1.1);
    car.stop();
    led1 = 0;
    wait(0.5);
    led1 = 1;

    // go straight
    info = 'w';
    encoder0.reset();
    car.goStraight(200);
    while(encoder0.get_cm()<20) wait_ms(50);
    car.stop();
    led1 = 0;
    wait(0.5);
    led1 = 1;

    // right
    info = 'd';
    car.turn(200, -0.2);
    wait(1.7);
    car.stop();
    led1 = 0;
    wait(0.5);
    led1 = 1;

    // go straight
    info = 'w';
    encoder0.reset();
    car.goStraight(200);
    while(encoder0.get_cm()<120) wait_ms(50);
    car.stop();
    led1 = 0;
    wait(0.5);
    led1 = 1;

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

void info_log(void){
  xbee.printf("%c\r\n", info);
}