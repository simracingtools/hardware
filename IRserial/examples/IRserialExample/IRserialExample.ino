
#include "IRserial.h"
#include <LiquidCrystalFast.h>

LiquidCrystalFast lcd1(0, 4, 1, 2, 3, 8, 9);
IRserial irSerial = IRserial(&Serial);

void setup(void) {
  Serial.begin(9200);
  lcd1.begin(16, 2);
}

void loop(void) {
  IRtelegram* telegram = irSerial.receiveTelegram();
  if( telegram->isValid() ) {
    if( telegram->isOfType("PFU") ) {
      lcd1.setCursor(0, 0);
      lcd1.print("Refuel: " + String(telegram->toFloatValue()) + " L");
    }
    if( telegram->isOfType("PFL") ) {
      lcd1.setCursor(0,1);
      lcd1.print("                ");
      
      int flags = telegram->toIntValue();
      String line = String("");
      if( flags & irPitFlags.lf_tire_change) {
        line += "LF ";
      }
      if( flags & irPitFlags.rf_tire_change) {
        line += "RF ";
      }
      if( flags & irPitFlags.rr_tire_change) {
        line += "RR ";
      }
      if( flags & irPitFlags.lr_tire_change) {
        line += "LR ";
      }
      if( flags & irPitFlags.fuel_fill) {
        line += "F ";
      }
      if( flags & irPitFlags.windshield_tearoff) {
        line += "W ";
      }
      if( flags & irPitFlags.fast_repair) {
        line += "R ";
      }

      lcd1.setCursor(0,1);
      lcd1.print(line);
      
      irSerial.sendPitCommand(irPitCmd.fuel);
      irSerial.sendRefuelAmount(85);
    }
  }
  delay(1000);  
}
