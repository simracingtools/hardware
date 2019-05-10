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

Bounce btnBb1 = Bounce(PIN_BTN_BB1, BOUNCE_TIME);
Bounce btnBb2 = Bounce(PIN_BTN_BB2, BOUNCE_TIME);
Bounce btnBbCar = Bounce(PIN_BTN_BBCAR, BOUNCE_TIME);
Bounce btnBbPit = Bounce(PIN_BTN_BBPIT, BOUNCE_TIME);
Encoder bb1Enc = Encoder(PINS_ENC_BB1);
Encoder bb2Enc = Encoder(PINS_ENC_BB2);

struct Config {
  int encSteps;
  int ledBrightness;
  bool joystickMode;
}; 

Config config = { ENC_STEPS, LED_BRIGHTNESS, JOYSTICK_MODE};
int rActive = -1;

void handleJoyButtonPress(int btn) {
  Joystick.button(btn, 1);
  delay(JOY_BTN_DURATION);
  Joystick.button(btn, 0);
}

void handleButtonJoy(Bounce* btn, int bntNum) {
  if(btn->fallingEdge()) {
    Joystick.button(bntNum, 1);
  }
  if(btn->risingEdge()) {
    Joystick.button(bntNum, 0);
  }
}

void handleBlackBoxBtn(Bounce*  btn, int btnNum, int relayPin) {
  handleButtonJoy(btn, btnNum);
  if( btn->fallingEdge() ) {
    if( rActive > 0 ) {
      digitalWrite(rActive, HIGH);
    }
    if( rActive != relayPin) {
      digitalWrite(relayPin, LOW);
      rActive = relayPin;
    } else {
      rActive = -1;
    }
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

// Update the button bounce objects
void updateButtons() {
  btnBb1.update();
  btnBb2.update();
  btnBbCar.update();
  btnBbPit.update();
}

void setup() {
  if( config.encSteps == 0 ) {
    config.encSteps = ENC_STEPS;
    config.ledBrightness = LED_BRIGHTNESS;
    config.joystickMode = JOYSTICK_MODE;
  }

  pinMode(PIN_BTN_BBCAR, INPUT_PULLUP);
  pinMode(PIN_BTN_BBPIT, INPUT_PULLUP);
  pinMode(PIN_BTN_BB1, INPUT_PULLUP);
  pinMode(PIN_BTN_BB2, INPUT_PULLUP);

  for( int i = 0; i < 8; i++ ) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH);
  }

  bb1Enc.write(0);
  bb2Enc.write(0);
}

void normalOpJoystick() {
  // Update all the buttons.  There should not be any long
  // delays in loop(), so this runs repetitively at a rate
  // faster than the buttons could be pressed and released.
  updateButtons();

  handleEncoderJoy(&bb1Enc, JOY_BTN_BB1_INC, JOY_BTN_BB1_DEC);
  handleEncoderJoy(&bb2Enc, JOY_BTN_BB2_INC, JOY_BTN_BB2_DEC);
  handleButtonJoy(&btnBb1, JOY_BTN_BB1_TOGGLE);
  handleButtonJoy(&btnBb2, JOY_BTN_BB2_TOGGLE);
  
  handleBlackBoxBtn(&btnBbPit, JOY_BTN_BB_PIT, PIN_R1);
  handleBlackBoxBtn(&btnBbCar, JOY_BTN_BB_CAR, PIN_R2);

}


void loop() {
  normalOpJoystick();

  delay(LOOP_DELAY);
}
