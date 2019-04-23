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

boolean btnJoyIgn = false;
boolean btnJoyPit = false;
boolean btnJoyTcr1Dec = false;
boolean btnJoyTcr1Inc = false;
boolean btnJoyTcr2Dec = false;
boolean btnJoyTcr2Inc = false;
boolean btnJoyAbsDec = false;
boolean btnJoyAbsInc = false;
boolean btnJoyEng1Dec = false;
boolean btnJoyEng1Inc = false;
boolean btnJoyEng2Dec = false;
boolean btnJoyEng2Inc = false;

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

  // Ignition Switch
  if( btnJoyIgn ) {
    Joystick.button(JOY_BTN_IGN, 0);
    btnJoyIgn = false;
  }
  if (swIgn.fallingEdge()) {
    //Keyboard.print("i");
    Joystick.button(JOY_BTN_IGN, 1);
    btnJoyIgn = true;
  }
  if( swIgn.risingEdge()) {
    //Keyboard.print("i");
    Joystick.button(JOY_BTN_IGN, 1);
    btnJoyIgn = true;
  }
 
  // Engine start button - continously
  if (btnStart.fallingEdge()) {
    Joystick.button(JOY_BTN_START, 1);
  }
  if( btnStart.risingEdge()) {
    Joystick.button(JOY_BTN_START, 0);
  }

  // ACC1 switch
  if( btnJoyPit ) {
    Joystick.button(JOY_BTN_PIT, 0);
    btnJoyPit = false;
  }
  if (swPit.fallingEdge()) {
    Joystick.button(JOY_BTN_PIT, 1);
    btnJoyPit = true;
  }
  if( swPit.risingEdge()) {
    Joystick.button(JOY_BTN_PIT, 1);
    btnJoyPit = true;
  }

  // TCR encoder push
  if (btnTcr.fallingEdge()) {
	  Joystick.button(JOY_BTN_TCR_TOGGLE, 1);
  }
  if( btnTcr.risingEdge()) {
	  Joystick.button(JOY_BTN_TCR_TOGGLE, 0);
  }

  newTcr = TCR.read();
  if(newTcr < -ENC_STEPS) {
    if( tcrMode ) {
    	btnJoyTcr1Dec = true;
    	Joystick.button(JOY_BTN_TCR1_DEC, 1);
    } else {
    	btnJoyTcr2Dec = true;
    	Joystick.button(JOY_BTN_TCR2_DEC, 1);
    }
    TCR.write(0);
   } else if( newTcr > ENC_STEPS ) {
    if( tcrMode ) {
    	btnJoyTcr1Inc = true;
    	Joystick.button(JOY_BTN_TCR1_INC, 1);
    } else {
    	btnJoyTcr2Inc = true;
    	Joystick.button(JOY_BTN_TCR2_INC, 1);
    }
    TCR.write(0);
  }

  if( btnJoyTcr1Dec ) {
	  btnJoyTcr1Dec = false;
  	Joystick.button(JOY_BTN_TCR1_DEC, 0);
  }
  if( btnJoyTcr2Dec ) {
	  btnJoyTcr2Dec = false;
  	Joystick.button(JOY_BTN_TCR2_DEC, 0);
  }
  if( btnJoyTcr1Inc ) {
	  btnJoyTcr1Inc = false;
  	Joystick.button(JOY_BTN_TCR1_INC, 0);
  }
  if( btnJoyTcr2Inc ) {
	  btnJoyTcr2Inc = false;
  	Joystick.button(JOY_BTN_TCR2_INC, 0);
  }

  // ABS encoder push
  if (btnAbs.fallingEdge()) {
	  Joystick.button(JOY_BTN_ABS_TOGGLE, 1);
  }
  if (btnAbs.risingEdge()) {
	  Joystick.button(JOY_BTN_ABS_TOGGLE, 0);
  }

  newAbs = ABS.read();
  if(newAbs < -ENC_STEPS) {
	  btnJoyAbsDec = true;
	  Joystick.button(JOY_BTN_ABS_DEC, 1);
    ABS.write(0);
  } else if( newAbs > ENC_STEPS ) {
	  btnJoyAbsInc = true;
	  Joystick.button(JOY_BTN_ABS_INC, 1);
    ABS.write(0);
  }
  if( btnJoyAbsDec ) {
	  btnJoyAbsDec = false;
	  Joystick.button(JOY_BTN_ABS_DEC, 0);
  }
  if( btnJoyAbsInc ) {
	  btnJoyAbsInc = false;
	  Joystick.button(JOY_BTN_ABS_INC, 0);
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
    	btnJoyEng1Dec = true;
    	Joystick.button(JOY_BTN_ENG1_DEC, 1);
    } else {
    	btnJoyEng2Dec = true;
    	Joystick.button(JOY_BTN_ENG2_DEC, 1);
    }
    ENG.write(0);
   } else if( newEng > ENC_STEPS ) {
    if( engMode ) {
    	btnJoyEng1Inc = true;
    	Joystick.button(JOY_BTN_ENG1_INC, 1);
    } else {
    	btnJoyEng2Inc = true;
    	Joystick.button(JOY_BTN_ENG2_INC, 1);
    }
    ENG.write(0);
  }
  if( btnJoyEng1Dec ) {
	  btnJoyEng1Dec = false;
  	Joystick.button(JOY_BTN_ENG1_DEC, 0);
  }
  if( btnJoyEng2Dec ) {
	  btnJoyEng2Dec = false;
  	Joystick.button(JOY_BTN_ENG2_DEC, 0);
  }
  if( btnJoyEng1Inc ) {
	  btnJoyEng1Inc = false;
  	Joystick.button(JOY_BTN_ENG1_INC, 0);
  }
  if( btnJoyEng2Inc ) {
	  btnJoyEng2Inc = false;
  	Joystick.button(JOY_BTN_ENG2_INC, 0);
  }

  delay(100);
}
