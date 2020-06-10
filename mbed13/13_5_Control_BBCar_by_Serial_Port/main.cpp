#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"

Ticker servo_ticker;
PwmOut pin9(D9), pin8(D8);
Serial pc(USBTX, USBRX);

BBCar car(pin8, pin9, servo_ticker);

int main() {

    char buf[256], outbuf[256];
    while (1) {
        for( int i=0; ;i++ ) {
            buf[i] = pc.getc();
            if(buf[i] == '\n') break;
        }

        RPC::call(buf, outbuf);
        pc.printf("%s\r\n", outbuf);
    }
}