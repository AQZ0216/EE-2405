#include "mbed.h"
#include "bbcar.h"

Ticker servo_ticker;
PwmOut pin8(D8), pin9(D9);

BBCar car(pin8, pin9, servo_ticker);

int main() {
    // please contruct you own calibration table with each servo
    double pwm_table0[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};
    double speed_table0[] = {-10.445, -9.812, -9.647, -9.408, -5.900, 0.000, 5.900, 10.843, 11.880, 11.401, 12.199};
    double pwm_table1[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};
    double speed_table1[] = {-10.445, -9.812, -9.647, -9.408, -5.900, 0.000, 5.900, 10.843, 11.880, 11.401, 12.199};

    // first and fourth argument : length of table
    car.setCalibTable(11, pwm_table0, speed_table0, 11, pwm_table1, speed_table1);

    while (1) {
        car.goStraightCalib(5);
        wait(5);
        car.stop();
        wait(5);
    }
}