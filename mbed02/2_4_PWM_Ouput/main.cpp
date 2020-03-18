#include "mbed.h"

PwmOut PWM1(D6);

int main() {
  PWM1.period(0.01);
  PWM1 = 0.5;
}