#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2);

int main()
{
      uLCD.printf("\nHello uLCD World\n"); //Default Green on black text
      wait(30);
}