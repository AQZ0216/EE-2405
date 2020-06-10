#include "mbed.h"
#include "arm_math.h"
#include "FXOS8700CQ.h"
#include "bbcar.h"
#include <math.h>
#include <stdlib.h>

#define bound 0.9

Serial pc(USBTX, USBRX);

Ticker servo_ticker;
PwmOut pin9(D9), pin8(D8);
BBCar car(pin8, pin9, servo_ticker);

FXOS8700CQ acc(PTD9, PTD8, (0x1D<<1));

float state[3] = {0};
float Kp = 0, Ki = 0, Kd = 0;
float a0 = 0, a1 = 0, a2 = 0;

//The formula is:
//y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]
//A0 = Kp + Ki + Kd
//A1 = (-Kp ) - (2 * Kd )
//A2 = Kd
void pid_init(){
    state[0] = 0;
    state[1] = 0;
    state[2] = 0;
    a0 = Kp + Ki + Kd;
    a1 = (-Kp) - 2*Kd;
    a2 = Kd;
}
float pid_process(float in){
    int out = in*a0 + a1*state[0] + a2*state[1] + state[2];

    //update state
    state[1] = state[0];
    state[0] = in;
    state[2] = out;

    return out;
}

int main(){
  //pid control setup
  Kp = 2.0; Ki = 1.0; Kd = 0;
  pid_init();

  //sensor setup
  acc.enable();
  SRAWDATA accel_data, magn_data;

  char rotation;
    char buff[256];
  float degree, target_degree, diff;

    while(1){
        wait(1);
        for( int i=0; i<1; i++ ) {
            rotation = pc.putc(pc.getc());
        }
        for( int i=0; i<2; i++ ) {
            buff[i] = pc.putc(pc.getc());
        }
        pc.printf("\r\n");

        int turn = atoi(buff);

        acc.get_data(&accel_data, &magn_data);
        degree = atan2(magn_data.y, magn_data.x) * 180 / PI;

      if(rotation == 'l'){
        target_degree = degree - turn;
      }else if(rotation == 'r'){
        target_degree = degree + turn;
      }else{
        target_degree = degree;
      }

        if(target_degree < -180){
            target_degree = 360 + target_degree;
        }else if(target_degree > 180){
            target_degree = 360 - target_degree;
        }
      diff = degree - target_degree;

      //The car will continue to turn to the target degree until the error is small enough
      while(abs(diff) > 8){
          //Process the PID control
          float correction = pid_process(diff);
          //bound the value from -0.9 to -.9
          correction = car.clamp(correction, bound, -bound);
          float turn = (rotation == 'l') ? (1-abs(correction)) : (-1+abs(correction));
          car.turn(car.turn2speed(turn),turn);
          wait(0.1);

          acc.get_data(&accel_data, &magn_data);
          degree = atan2(magn_data.y, magn_data.x) * 180 / PI;

          diff = degree - target_degree;
          pc.printf("degree:%f, target: %f, diff:%f \r\n", degree, target_degree, diff);
      }
      car.stop();
      pid_init();
    }
}