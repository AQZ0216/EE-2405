#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2);
PwmOut PWM1(D6);
Serial pc( USBTX, USBRX );
//AnalogIn Ain(A0);
DigitalIn  Din(D7);

int sample = 128;

float ADCdata[128];

int j = 0;

int main()
{
    uLCD.printf("\n106061151\n"); //Default Green on black text
    uLCD.line(50, 50 , 50, 100, RED);
    uLCD.line(50, 100 , 100, 100, RED);
    uLCD.line(100, 100 , 100, 50, RED);
    uLCD.line(100, 50 , 50, 50, RED);
      
    PWM1.period(0.001);
    PWM1 = 0.5;

    for (int i = 0; i < sample; i++){
        ADCdata[i] = Din;
        wait(1/sample);
    }

    PWM1 = 0;
    while (1){
        for (int i = 0; i < 10; i++){
            PWM1 = PWM1 + 0.1;
            pc.printf("%1.3f\r\n", ADCdata[j]);
            j++;
            wait(0.1);
        }
        for (int i = 0; i < 10; i++){
            PWM1 = PWM1 - 0.1;
            pc.printf("%1.3f\r\n", ADCdata[j]);
            j++;
            wait(0.1);
        }
    }
}