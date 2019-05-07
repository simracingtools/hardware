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
#include <EEPROM.h>
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

bool btnJoy[33];

struct Config {
	int encSteps;
	int ledBrightness;
	bool joystickMode;
}; 

Config config = { ENC_STEPS, LED_BRIGHTNESS, JOYSTICK_MODE};

void setup() {
  // Initially disable config mode
  configMode = false;

  // Set initial config values, first try to read from EEPROM
  EEPROM.get(CONFIG_ADDRESS, config);
  if( config.encSteps == 0 ) {
    config.encSteps = ENC_STEPS;
    config.ledBrightness = LED_BRIGHTNESS;
    config.joystickMode = JOYSTICK_MODE;
  }
  
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

  // Initialize engine mode and set initial LED state to reflect
  // operation mode after power on
  engMode = config.joystickMode;
  if( engMode ) {
    analogWrite(PIN_LED_RED, 0);
    analogWrite(PIN_LED_BLUE, config.ledBrightness);
  } else {
    analogWrite(PIN_LED_RED, config.ledBrightness);
    analogWrite(PIN_LED_BLUE, 0);
  }
}

// Handle an encoder. The encoder is only checked for turn direction,
// it behaves like an up/down switch.
void handleEncoderKey(Encoder* enc, String up, String down) {
  long encVal = enc->read();
  if(encVal < (-1 * config.encSteps)) {
    Keyboard.print(down);
    enc->write(0);
  } else if( encVal > config.encSteps ) {
    Keyboard.print(up);
    enc->write(0);
  }
}

void handleEncoderJoy(Encoder* enc, int up, int down) {
  long encVal = enc->read();
  if(encVal < (-1 * config.encSteps)) {
    handleJoyButtonPress(down);
    enc->write(0);
  } else if( encVal > config.encSteps ) {
    handleJoyButtonPress(up);
    enc->write(0);
  }
}

// Handle a momentary push button. Used for the push function
// of the encoders and the engine start button. 
void handleButtonKey(Bounce* btn, int key) {
  if(btn->fallingEdge()) {
    Keyboard.press(key);
  }
  if(btn->risingEdge()) {
    Keyboard.release(key);
  }
}

void handleButtonJoy(Bounce* btn, int bntNum) {
  if(btn->fallingEdge()) {
    Joystick.button(bntNum, 1);
  }
  if(btn->risingEdge()) {
    Joystick.button(bntNum, 0);
  }
}

// Handle a on/off switch. Each state change of the switch behaves like a
// momentary button press. The switch position is not relevant.
void handleSwitchKey(Bounce* sw, String key) {
  if(sw->fallingEdge()) {
    Keyboard.print(key);
  }
  if(sw->risingEdge()) {
    Keyboard.print(key);
  }
}

void handleSwitchJoy(Bounce* sw, int btn) {
  if(sw->fallingEdge()) {
    handleJoyButtonPress(btn);
  }
  if(sw->risingEdge()) {
    handleJoyButtonPress(btn);
  }
}

void handleJoyButtonPress(int btn) {
  Joystick.button(btn, 1);
  btnJoy[btn] = true;
}

void handleJoystickRelease() {
  int i;
  for( i = 1; i < 33; i++ ) {
    if( btnJoy[i] ) {
      Joystick.button(i, 0);
      btnJoy[i] = false;
    }
  }
}

void checkEngMode() {
  if (btnEng.risingEdge()) {
    engMode = !engMode;
    if( engMode ) {
      analogWrite(PIN_LED_RED, 0);
      analogWrite(PIN_LED_BLUE, config.ledBrightness);
    } else {
      analogWrite(PIN_LED_RED, config.ledBrightness);
      analogWrite(PIN_LED_BLUE, 0);
    }
  }
}

void updateButtons() {
  swIgn.update();
  btnStart.update();
  swPit.update();
  btnEng.update();
  btnAbs.update();
  btnTcr.update();
}

void normalOpKeyboard() {
  boolean tcrMode;

  // update the button objects
  updateButtons();

  // Ignition Switch
  handleSwitchKey(&swIgn, KEY_IGN);

  // Engine start button
  handleButtonKey(&btnStart, KEY_START);

  // ACC1 switch - pit limiter
  handleSwitchKey(&swPit, KEY_PIT);

  // ACC2 switch - switch position controls which TC is changed by the encoder
  tcrMode = digitalRead(PIN_SW_TCR);

  // TCR encoder
  handleButtonKey(&btnTcr, KEY_TCR_TOGGLE);

  if( tcrMode ) {
      handleEncoderKey(&TCR, KEY_TCR1_INC, KEY_TCR1_DEC);
  } else {
      handleEncoderKey(&TCR, KEY_TCR2_INC, KEY_TCR2_DEC);
  }

  // ABS encoder
  handleButtonKey(&btnAbs, KEY_ABS_TOGGLE);
  handleEncoderKey(&ABS, KEY_ABS_INC, KEY_ABS_DEC);
  
  // ENG encoder push - toggles between two engine settings and reflect
  // the selected setting by changing LED status.
  checkEngMode();
  
  // ENG encoder
  if( engMode ) {
	  handleEncoderKey(&ENG, KEY_ENG1_INC, KEY_ENG1_DEC);
  } else {
  	handleEncoderKey(&ENG, KEY_ENG2_INC, KEY_ENG2_DEC);
  }
}

void normalOpJoystick() {
  boolean tcrMode;

  handleJoystickRelease();
  // update the button objects
  updateButtons();

  // Ignition Switch
  handleSwitchJoy(&swIgn, JOY_BTN_IGN);

  // Engine start button
  handleButtonJoy(&btnStart, JOY_BTN_START);

  // ACC1 switch - pit limiter
  handleSwitchJoy(&swPit, JOY_BTN_PIT);

  // ACC2 switch - switch position controls which TC is changed by the encoder
  tcrMode = digitalRead(PIN_SW_TCR);

  // TCR encoder
  handleButtonJoy(&btnTcr, JOY_BTN_TCR_TOGGLE);

  if( tcrMode ) {
      handleEncoderJoy(&TCR, JOY_BTN_TCR1_INC, JOY_BTN_TCR1_DEC);
  } else {
      handleEncoderJoy(&TCR, JOY_BTN_TCR2_INC, JOY_BTN_TCR2_DEC);
  }

  // ABS encoder
  handleButtonJoy(&btnAbs, JOY_BTN_ABS_TOGGLE);
  handleEncoderJoy(&ABS, JOY_BTN_ABS_INC, JOY_BTN_ABS_DEC);
  
  // ENG encoder push - toggles between two engine settings and reflect
  // the selected setting by changing LED status.
  checkEngMode();
  
  // ENG encoder
  if( engMode ) {
	  handleEncoderJoy(&ENG, JOY_BTN_ENG1_INC, JOY_BTN_ENG1_DEC);
  } else {
  	handleEncoderJoy(&ENG, JOY_BTN_ENG2_INC, JOY_BTN_ENG2_DEC);
  }
}

void blinkLed(int pin, int times, int ms) {
  for( int i = 0; i < times; i++ ) {
    digitalWrite(pin, LOW);
    delay(ms);
    digitalWrite(pin, HIGH);
  }  
  analogWrite(pin, config.ledBrightness);
}

void configOp() {
  // Light up both LED to signal config mode
  analogWrite(PIN_LED_RED, config.ledBrightness);
  analogWrite(PIN_LED_BLUE, config.ledBrightness);
  btnEng.update();
  btnAbs.update();
  btnTcr.update();

  // ENG encoder controls LED brightness;
  config.ledBrightness = ENG.read();
  if(btnEng.risingEdge()) {
    //Keyboard.println("LED brightness " + String(config.ledBrightness));
  }

  // ABS encoder controls encoder sensitivity
  config.encSteps = ABS.read();
  if( config.encSteps < 4 ) {
    config.encSteps = 4;
    ABS.write(config.encSteps);
  }
  if(btnAbs.risingEdge()) {
    //Keyboard.println("Encoder sensitivitz " + String(config.encSteps));
    blinkLed(PIN_LED_BLUE, config.encSteps, 300);
  }
  
  // TCR encoder push toggles between joystick and keyboard mode
  if( btnTcr.risingEdge() ) {
    if( config.joystickMode != 0 ) {
      config.joystickMode = false;
    } else {
      config.joystickMode = true;
    }
    //config.joystickMode = !config.joystickMode;
    if( config.joystickMode ) {
      blinkLed(PIN_LED_BLUE, 2, 500);
    } else {
      blinkLed(PIN_LED_RED, 2, 500);
    }
  }
}

// Determine if config mode has to entered or not
void checkConfigMode() {
  if( digitalRead(PIN_SW_IGN) ) {
    // Ignition switch must be off
    if( !digitalRead(PIN_BTN_ENG) && !digitalRead(PIN_BTN_ABS) ) {
      // Enter config mode if ENG and ABS encoders are pushed the same time
      TCR.write(0);
      ABS.write(config.encSteps);
      ENG.write(config.ledBrightness);
      configMode = true;
    }
  } else if( configMode ) {
    // Toggling ignition switch leaves config mode.
    EEPROM.put(CONFIG_ADDRESS, config);
    if( engMode ) {
      analogWrite(PIN_LED_RED, 0);
      analogWrite(PIN_LED_BLUE, config.ledBrightness);
    } else {
      analogWrite(PIN_LED_RED, config.ledBrightness);
      analogWrite(PIN_LED_BLUE, 0);
    }
    configMode = false;
  }
}

// Sketch main loop
void loop() {

  // Determine if to enter config mode.
  checkConfigMode();

  if( configMode ) {
    configOp();
  } else {
    if( config.joystickMode ) {
      normalOpJoystick();
    } else {
      normalOpKeyboard();
    }
  }

  delay(100);
}
