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

// Create Bounce objects for each button.  The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.
// 10 = 10 ms debounce time, here defined in config.h
Bounce swIgn = Bounce(PIN_SW_IGN, BOUNCE_TIME);
Bounce btnStart = Bounce(PIN_BTN_START, BOUNCE_TIME);
Bounce swPit = Bounce(PIN_SW_PIT, BOUNCE_TIME);
Bounce btnEng = Bounce(PIN_BTN_ENG, BOUNCE_TIME);
Bounce btnAbs = Bounce(PIN_BTN_ABS, BOUNCE_TIME);
Bounce btnTcr = Bounce(PIN_BTN_TCR, BOUNCE_TIME);

// Create encoder objects for the three encoders
Encoder ENG(PINS_ENC_ENG);
Encoder ABS(PINS_ENC_ABS);
Encoder TCR(PINS_ENC_TCR);

// Encoder ENG has two functions depending this value;
bool engMode, configMode;
int  encSteps, ledBrightness;

void setup() {
  // Initially disable config mode
  configMode = false;

  // Set initial config values
  encSteps = ENC_STEPS;
  ledBrightness = LED_BRIGHTNESS;
  
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
  
  // Configure output pins for the red and blue LED
  pinMode(PIN_LED_RED, OUTPUT);        // red LED
  pinMode(PIN_LED_BLUE, OUTPUT);       // blue LED

  // Initialize the encoders with position zero.
  TCR.write(0);
  ABS.write(0);
  ENG.write(0);

  // Initialize engine mode and set initial LED state
  engMode = false;
  analogWrite(PIN_LED_RED, ledBrightness);
  analogWrite(PIN_LED_BLUE, 0);
}

// Handle an encoder. The encoder is only checked for turn direction,
// it behaves like an up/down switch.
void handleEncoder(Encoder* enc, String up, String down) {
  long encVal = enc->read();
  if(encVal < (-1 * encSteps)) {
    Keyboard.print(down);
    enc->write(0);
  } else if( encVal > encSteps ) {
    Keyboard.print(up);
    enc->write(0);
  }
}

// Handle a momentary push button. Used for the push function
// of the encoders and the engine start button. 
void handleButton(Bounce* btn, int key) {
  if(btn->fallingEdge()) {
    Keyboard.press(key);
  }
  if(btn->risingEdge()) {
    Keyboard.release(key);
  }
}

// Handle a on/off switch. Each state change of the switch behaves like a
// momentary button press. The switch position is not relevant.
void handleSwitch(Bounce* sw, String key) {
  if(sw->fallingEdge()) {
    Keyboard.print(key);
  }
  if(sw->risingEdge()) {
    Keyboard.print(key);
  }
}

void normalOp() {
  boolean tcrMode;

  // update the button objects
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

  // ACC2 switch - switch position controls which TC is changed by the encoder
  tcrMode = digitalRead(PIN_SW_TCR);

  // TCR encoder
  handleButton(&btnTcr, KEY_TCR_TOGGLE);

  if( tcrMode ) {
      handleEncoder(&TCR, KEY_TCR1_INC, KEY_TCR1_DEC);
  } else {
      handleEncoder(&TCR, KEY_TCR2_INC, KEY_TCR2_DEC);
  }

  // ABS encoder
  handleButton(&btnAbs, KEY_ABS_TOGGLE);
  handleEncoder(&ABS, KEY_ABS_INC, KEY_ABS_DEC);
  
  // ENG encoder push - toggles between two engine settings and reflect
  // the selected setting by changing LED status.
  if (btnEng.risingEdge()) {
    engMode = !engMode;
    if( engMode ) {
      analogWrite(PIN_LED_RED, 0);
      analogWrite(PIN_LED_BLUE, ledBrightness);
    } else {
      analogWrite(PIN_LED_RED, ledBrightness);
      analogWrite(PIN_LED_BLUE, 0);
    }
  }
  
  // ENG encoder
  if( engMode ) {
	handleEncoder(&ENG, KEY_ENG1_INC, KEY_ENG1_DEC);
  } else {
  	handleEncoder(&ENG, KEY_ENG2_INC, KEY_ENG2_DEC);
  }
}

void configOp() {
  // Light up both LED to signal config mode
  analogWrite(PIN_LED_RED, ledBrightness);
  analogWrite(PIN_LED_BLUE, ledBrightness);
  btnEng.update();
  btnAbs.update();

  // ENG encoder controls LED brightness;
  ledBrightness = ENG.read();
  if(btnEng.risingEdge()) {
    Keyboard.println("LED brightness " + String(ledBrightness));
  }

  // ABS encoder controls encoder sensitivity
  encSteps = ABS.read();
  if(btnAbs.risingEdge()) {
    Keyboard.println("Encoder sensitivitz " + String(encSteps));
  }
}

// Sketch main loop
void loop() {

  // Determine if to enter config mode.
  if( digitalRead(PIN_SW_IGN) ) {
    // Ignition switch must be off
    if( !digitalRead(PIN_BTN_ENG) && !digitalRead(PIN_BTN_ABS) ) {
      // Enter config mode if ENG and ABS encoders are pushed the same time
      configMode = true;
      TCR.write(0);
      ABS.write(encSteps);
      ENG.write(ledBrightness);
    }
  } else {
    // Toggling ignition switch leaves config mode. 
    configMode = false;
    if( engMode ) {
      analogWrite(PIN_LED_RED, 0);
      analogWrite(PIN_LED_BLUE, ledBrightness);
    } else {
      analogWrite(PIN_LED_RED, ledBrightness);
      analogWrite(PIN_LED_BLUE, 0);
    }
  }

  if( configMode ) {
    configOp();
  } else {
    normalOp();
  }

  delay(50);
}
