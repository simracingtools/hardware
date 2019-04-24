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

#define RED_OFF analogWrite(PIN_LED_RED, 0)
#define RED_ON analogWrite(PIN_LED_RED, LED_BRIGHTNESS)
#define BLUE_OFF analogWrite(PIN_LED_BLUE, 0)
#define BLUE_ON analogWrite(PIN_LED_BLUE, LED_BRIGHTNESS)

// Create Bounce objects for each button.  The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.
// 10 = 10 ms debounce time
Bounce swIgn = Bounce(PIN_SW_IGN, BOUNCE_TIME);
Bounce btnStart = Bounce(PIN_BTN_START, BOUNCE_TIME);
Bounce swPit = Bounce(PIN_SW_PIT, BOUNCE_TIME);
Bounce btnEng = Bounce(PIN_BTN_ENG, BOUNCE_TIME);
Bounce btnAbs = Bounce(PIN_BTN_ABS, BOUNCE_TIME);
Bounce btnTcr = Bounce(PIN_BTN_TCR, BOUNCE_TIME);

Encoder ENG(PINS_ENC_ENG);
Encoder ABS(PINS_ENC_ABS);
Encoder TCR(PINS_ENC_TCR);

boolean engMode;

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

void handleEncoder(Encoder* enc, String up, String down) {
  long encVal = enc->read();
  if(encVal < -ENC_STEPS) {
    Keyboard.print(down);
    enc->write(0);
  } else if( encVal > ENC_STEPS ) {
    Keyboard.print(up);
    enc->write(0);
  }
}

void handleButton(Bounce* btn, int key) {
  if(btn->fallingEdge()) {
    Keyboard.press(key);
  }
  if(btn->risingEdge()) {
    Keyboard.release(key);
  }
}

void handleSwitch(Bounce* sw, String key) {
  if(sw->fallingEdge()) {
    Keyboard.print(key);
  }
  if(sw->risingEdge()) {
    Keyboard.print(key);
  }
}

void loop() {
  boolean tcrMode;
  
  swIgn.update();
  btnStart.update();
  swPit.update();
  btnEng.update();
  btnAbs.update();
  btnTcr.update();

  // Ignition Switch
  handleSwitch(&swIgn, KEY_IGN);

  // Engine start button
  handleButton(&btnStart, KEY_START);

  // ACC1 switch - pit limiter
  handleSwitch(&swPit, KEY_PIT);

  // TCR encoder
  handleButton(&btnTcr, KEY_TCR_TOGGLE);

  tcrMode = digitalRead(PIN_SW_TCR);
  if( tcrMode ) {
      handleEncoder(&TCR, KEY_TCR1_INC, KEY_TCR1_DEC);
  } else {
      handleEncoder(&TCR, KEY_TCR2_INC, KEY_TCR2_DEC);
  }

  // ABS encoder
  handleButton(&btnAbs, KEY_ABS_TOGGLE);
  handleEncoder(&ABS, KEY_ABS_INC, KEY_ABS_DEC);
  
  // ENG encoder push
  if (btnEng.risingEdge()) {
    engMode = !engMode;
  }
  if( engMode ) {
    RED_OFF;
    BLUE_ON;
	handleEncoder(&ENG, KEY_ENG1_INC, KEY_ENG1_DEC);
  } else {
    RED_ON;
    BLUE_OFF;
  	handleEncoder(&ENG, KEY_ENG2_INC, KEY_ENG2_DEC);
  }
  
  delay(50);
}
