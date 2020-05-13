#include "mbed.h"
#include "TextLCD.h"
#include "mbed_rpc.h"
void doDisplay(Arguments *in, Reply *out);
void doLocate(Arguments *in, Reply *out);
RPCFunction rpcdisplay(&doDisplay, "doDisplay");
RPCFunction rpclocate(&doLocate, "doLocate");
// Host PC Communication channels
Serial pc(USBTX, USBRX); // tx, rx

// I2C Communication
I2C i2c_lcd(D14,D15); // SDA, SCL

TextLCD_I2C lcd(&i2c_lcd, 0x4E, TextLCD::LCD16x2);  // I2C bus, PCF8574 Slaveaddress, LCD Type

int main() {
   lcd.setCursor(TextLCD::CurOff_BlkOn);
   char buf[256], outbuf[256];

   while(1) {
      memset(buf, 0, 256);
      for (int i = 0; ; i++) {
          char recv = pc.getc();
          if (recv == '\r') {
              pc.printf("\r\n");
              break;
          }

          buf[i] = pc.putc(recv);
      }

      //Call the static call method on the RPC class
      RPC::call(buf, outbuf);

      pc.printf("%s\r\n", outbuf);

   }

}
void doDisplay(Arguments *in, Reply *out) {
   const char *tmp = in->getArg<const char*>();
   pc.printf("[str arg]%s", tmp);
   for(int i = 0; tmp[i] != 0; i++) {
      lcd.putc(tmp[i]);
   }

}

void doLocate(Arguments *in, Reply *out) {
   int x = in->getArg<int>();
   int y = in->getArg<int>();
   lcd.locate(x,y);
   pc.printf("locate (col,row)=(%d,%d)", x, y);
}