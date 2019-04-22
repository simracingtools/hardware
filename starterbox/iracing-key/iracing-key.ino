/* 
    Starterbox for iRacing motorsport simulation.
    You must select Keyboard from the "Tools > USB Type" menu
    This code is based on Teensyduino public domain example code.
    Copyright (C) 2019  Robert Bausdorf

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/
#include <Bounce.h>
#include <Encoder.h>
#include "config.h"

#define RED_OFF digitalWrite(PIN_LED_RED, LOW)
#define RED_ON digitalWrite(PIN_LED_RED, HIGH)
#define BLUE_OFF digitalWrite(PIN_LED_BLUE, LOW)
#define BLUE_ON digitalWrite(PIN_LED_BLUE, HIGH)

// Create Bounce objects for each button.  The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.
// 10 = 10 ms debounce time
Bounce swIgn = Bounce(PIN_SW_IGN, BOUNCE_TIME);
Bounce btnStart = Bounce(PIN_BTN_START, BOUNCE_TIME);
Bounce swPit = Bounce(PIN_SW_PIT, BOUNCE_TIME);
//Bounce swTcr = Bounce(PIN_SW_TCR, BOUNCE_TIME);
Bounce btnEng = Bounce(PIN_BTN_ENG, BOUNCE_TIME);
Bounce btnAbs = Bounce(PIN_BTN_ABS, BOUNCE_TIME);
Bounce btnTcr = Bounce(PIN_BTN_TCR, BOUNCE_TIME);

Encoder ENG(PINS_ENC_ENG);
Encoder ABS(PINS_ENC_ABS);
Encoder TCR(PINS_ENC_TCR);

boolean tcrMode, engMode;

void setup() {
  // Configure the pins for input mode with pullup resistors.
  // The pushbuttons connect from each pin to ground.  When
  // the button is pressed, the pin reads LOW because the button
  // shorts it to ground.  When released, the pin reads HIGH
  // because the pullup resistor connects to +5 volts inside
  // the chip.  LOW for "on", and HIGH for "off" may seem
  // backwards, but using the on-chip pullup resistors is very
  // convenient.  The scheme is called "active low", and it's
  // very commonly used in electronics... so much that the chip
  // has built-in pullup resistors!
  pinMode(PIN_SW_IGN, INPUT_PULLUP);
  pinMode(PIN_BTN_START, INPUT_PULLUP);
  pinMode(PIN_SW_PIT, INPUT_PULLUP);
  pinMode(PIN_SW_TCR, INPUT_PULLUP);
  pinMode(PIN_BTN_ENG, INPUT_PULLUP);
  pinMode(PIN_BTN_ABS, INPUT_PULLUP);
  pinMode(PIN_BTN_TCR, INPUT_PULLUP);
  pinMode(PIN_LED_RED, OUTPUT);        // red LED
  pinMode(PIN_LED_BLUE, OUTPUT);       // blue LED

  TCR.write(0);
  ABS.write(0);
  ENG.write(0);

  engMode = false;
  RED_ON; 
  BLUE_OFF;
}


void loop() {
  // Update all the buttons.  There should not be any long
  // delays in loop(), so this runs repetitively at a rate
  // faster than the buttons could be pressed and released.
  swIgn.update();
  btnStart.update();
  swPit.update();
  //swTcr.update();
  btnEng.update();
  btnAbs.update();
  btnTcr.update();
  tcrMode = digitalRead(PIN_SW_TCR);

  long newTcr, newAbs, newEng;
  
  // Check each button for "falling" edge.
  // Type a message on the Keyboard when each button presses
  // Update the Joystick buttons only upon changes.
  // falling = high (not pressed - voltage from pullup resistor)
  //           to low (pressed - button connects pin to ground)

  // Ignition Switch
  if (swIgn.fallingEdge()) {
    Keyboard.print(KEY_IGN);
  }
  if( swIgn.risingEdge()) {
    Keyboard.print(KEY_IGN);
  }

  // Engine start button - continously
  if (btnStart.fallingEdge()) {
    Keyboard.press(KEY_START);
  }
  if( btnStart.risingEdge()) {
    Keyboard.release(KEY_START);
  }

  // ACC1 switch - pit limiter
  if (swPit.fallingEdge()) {
    Keyboard.print(KEY_PIT);
  }
  if( swPit.risingEdge()) {
    Keyboard.print(KEY_PIT);
  }

  // TCR encoder push
  if (btnTcr.fallingEdge()) {
    Keyboard.press(KEY_TCR_TOGGLE);
  }
  if( btnTcr.risingEdge()) {
    Keyboard.release(KEY_TCR_TOGGLE);
  }

  newTcr = TCR.read();
  if(newTcr < -ENC_STEPS) {
    if( tcrMode ) {
      Keyboard.print(KEY_TCR1_DEC);
    } else {
      Keyboard.print(KEY_TCR2_DEC);
    }
    TCR.write(0);
   } else if( newTcr > ENC_STEPS ) {
    if( tcrMode ) {
      Keyboard.print(KEY_TCR1_INC);
    } else {
      Keyboard.print(KEY_TCR2_INC);
    }
    TCR.write(0);
  }

  // ABS encoder push
  if (btnAbs.fallingEdge()) {
    Keyboard.press(KEY_ABS_TOGGLE);
  }
  if (btnAbs.risingEdge()) {
    Keyboard.release(KEY_ABS_TOGGLE);
  }
 
  newAbs = ABS.read();
  if(newAbs < -ENC_STEPS) {
    Keyboard.print(KEY_ABS_DEC);
    ABS.write(0);
  } else if( newAbs > ENC_STEPS ) {
    Keyboard.print(KEY_ABS_INC);
    ABS.write(0);
  }
  
  // ENG encoder push
  if (btnEng.risingEdge()) {
    engMode = !engMode;
  }
  if( engMode ) {
      RED_OFF;
      BLUE_ON;
  } else {
      RED_ON;
      BLUE_OFF;
  }
  
  newEng = ENG.read();
  if(newEng < -ENC_STEPS) {
    if( engMode ) {
      Keyboard.print(KEY_ENG1_DEC);
    } else {
      Keyboard.print(KEY_ENG2_DEC);
    }
    ENG.write(0);
   } else if( newEng > ENC_STEPS ) {
    if( engMode ) {
      Keyboard.print(KEY_ENG1_INC);
    } else {
      Keyboard.print(KEY_ENG2_INC);
    }
    ENG.write(0);
  }
 

  delay(50);
}
