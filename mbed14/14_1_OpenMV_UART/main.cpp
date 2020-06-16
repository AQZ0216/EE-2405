#include"mbed.h"

Thread thread1;
Thread thread2;

Serial pc(USBTX,USBRX); //tx,rx
Serial uart(D12,D11); //tx,rx
DigitalIn button(SW2);

void recieve_thread(){
   while(1) {
      if(uart.readable()){
            char recv = uart.getc();
            pc.putc(recv);
            pc.printf("\r\n");
      }
   }
}

void send_thread(){
   while(1){
      if( button == 0){
         char s[21];
         sprintf(s,"image_classification");
         uart.puts(s);
         pc.printf("send\r\n");
         wait(0.5);
      }
   }
}

int main(){
   uart.baud(9600);
   thread1.start(send_thread);
   thread2.start(recieve_thread);
}