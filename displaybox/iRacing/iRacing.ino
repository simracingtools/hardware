
#include <U8g2lib.h>
#include <Wire.h>
#include <LiquidCrystalFast.h>

#include "IRserial.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

LiquidCrystalFast lcd1(0, 4, 1, 2, 3, 8, 9);

IRserial irSerial = IRserial(&Serial);

void setup(void) {
  Serial.begin(9200);
  u8g2.begin();
  lcd1.begin(16, 2);
  lcd1.print("Hello World");
}

void loop(void) {
  IRtelegram* telegram = irSerial.receiveTelegram();
  if( telegram->isValid() ) {
    if( String("PFU").equals(String(telegram->_type))) {
      u8g2.clearBuffer();          // clear the internal memory
      u8g2.sendBuffer();          // transfer internal memory to the display
      u8g2.setFont(u8g2_font_inb46_mn);
      //u8g2.setFont(u8g2_font_ncenB08_tr);  // choose a suitable font
      u8g2.drawStr(0,55,telegram->_value);  // write something to the internal memory
      u8g2.sendBuffer();          // transfer internal memory to the display
    } else {
      lcd1.setCursor(0, 0);
      lcd1.print(String(telegram->_type) + "=" + String(telegram->_value));
      irSerial.sendPitCommand(irPitCmd.fuel);
      irSerial.sendRefuelAmount(85);
    }
  }
  lcd1.setCursor(0,1);
  lcd1.print(millis()/1000);
  delay(1000);  
}
