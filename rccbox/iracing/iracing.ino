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
Bounce btnRa1 = Bounce(PIN_BTN_RA1, BOUNCE_TIME);
Bounce btnRa2 = Bounce(PIN_BTN_RA2, BOUNCE_TIME);
Bounce btnFuel = Bounce(PIN_BTN_FUEL, BOUNCE_TIME);

Bounce btnBbCar = Bounce(PIN_BTN_BBCAR, BOUNCE_TIME);
Bounce btnBbPit = Bounce(PIN_BTN_BBPIT, BOUNCE_TIME);
Bounce btnBbFuel = Bounce(PIN_BTN_BBFUEL, BOUNCE_TIME);
Bounce btnBbTyre = Bounce(PIN_BTN_BBTYRE, BOUNCE_TIME);
Bounce btnBbPabs = Bounce(PIN_BTN_BBPABS, BOUNCE_TIME);
Bounce btnBbPrel = Bounce(PIN_BTN_BBPREL, BOUNCE_TIME);
Bounce btnBbLap = Bounce(PIN_BTN_BBLAP, BOUNCE_TIME);

Bounce btnExit = Bounce(PIN_BTN_EXIT, BOUNCE_TIME);
Bounce btnClearTy = Bounce(PIN_BTN_TY_CLEAR, BOUNCE_TIME);

Bounce swViewUp = Bounce(PIN_SW_VIEW_UP, BOUNCE_TIME);
Bounce swViewDn = Bounce(PIN_SW_VIEW_DN, BOUNCE_TIME);

Bounce swTyreUp = Bounce(PIN_SW_TY_FR, BOUNCE_TIME);
Bounce swTyreDn = Bounce(PIN_SW_TY_RL, BOUNCE_TIME);

Encoder bb1Enc = Encoder(PINS_ENC_BB1);
Encoder bb2Enc = Encoder(PINS_ENC_BB2);
Encoder ra1Enc = Encoder(PINS_ENC_RA1);
Encoder ra2Enc = Encoder(PINS_ENC_RA2);
Encoder fuelEnc = Encoder(PINS_ENC_FUEL);

struct Config {
  int encSteps;
  int ledBrightness;
  bool joystickMode;
}; 

Config config = { ENC_STEPS, LED_BRIGHTNESS, JOYSTICK_MODE};
int rActive = -1;
int amountFuel = 0;
int changeTyreR, changeTyreF = 0;

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

void handleButtonKey(Bounce* btn, int keyNum) {
  if(btn->fallingEdge()) {
    Keyboard.press(keyNum);
  }
  if(btn->risingEdge()) {
    Keyboard.release(keyNum);
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

void handleButtonMacro(Bounce*  btn, String macro) {
  if(btn->risingEdge()) {
    Keyboard.println(macro);
  }
}

void handleTyreButtons() {

  if(btnClearTy.risingEdge()) {
    Keyboard.println(TXT_CLEAR_TYRES);
    changeTyreF = 0;
    changeTyreR = 0;
  }

  if( digitalRead(PIN_SW_O_R) ) {
    if(swTyreUp.risingEdge()) {
      Keyboard.println(TXT_TYRES_RIGHT);
     changeTyreF = 1;
    }
    if(swTyreDn.risingEdge()) {
      Keyboard.println(TXT_TYRES_LEFT);
     changeTyreR = 1;
    }
  } else {
    if(swTyreUp.risingEdge()) {
      Keyboard.println(TXT_TYRES_FRONT);
     changeTyreF = 1;
    }
    if(swTyreDn.risingEdge()) {
      Keyboard.println(TXT_TYRES_REAR);
     changeTyreR = 1;
    }
  }
  if( changeTyreR ) {
    analogWrite(PIN_LED_PWM, config.ledBrightness);
  } else {
    analogWrite(PIN_LED_PWM, 0);
  }
  if( changeTyreF ) {
    digitalWrite(PIN_LED_13, HIGH);
  } else {
    digitalWrite(PIN_LED_13, LOW);
  }
}

void handleEncoderFuel(Encoder* enc) {
  long encVal = enc->read();
  if(encVal < (-1 * config.encSteps)) {
    amountFuel --;
    Keyboard.println(TXT_FUEL + String(amountFuel));
    enc->write(0);
  } else if( encVal > config.encSteps ) {
    amountFuel ++;
    Keyboard.println(TXT_FUEL + String(amountFuel));
    enc->write(0);
  }
}

void handleFuel() {
  if(btnFuel.risingEdge()) {
    Keyboard.println(TXT_CLEAR_FUEL);
    amountFuel = 0;
  }
  handleEncoderFuel(&fuelEnc);
}

// Update the button bounce objects
void updateButtons() {
  btnBb1.update();
  btnBb2.update();
  btnRa1.update();
  btnRa2.update();
  btnFuel.update();
  
  btnBbCar.update();
  btnBbPit.update();
  btnBbFuel.update();
  btnBbTyre.update();
  btnBbPabs.update();
  btnBbPrel.update();
  btnBbLap.update();

  btnExit.update();
  btnClearTy.update();
  swViewUp.update();
  swViewDn.update();
  swTyreUp.update();
  swTyreDn.update();
}

void setup() {
  if( config.encSteps == 0 ) {
    config.encSteps = ENC_STEPS;
    config.ledBrightness = LED_BRIGHTNESS;
    config.joystickMode = JOYSTICK_MODE;
  }

  pinMode(PIN_BTN_BBCAR, INPUT_PULLUP);
  pinMode(PIN_BTN_BBPIT, INPUT_PULLUP);
  pinMode(PIN_BTN_BBFUEL, INPUT_PULLUP);
  pinMode(PIN_BTN_BBTYRE, INPUT_PULLUP);
  pinMode(PIN_BTN_BBPABS, INPUT_PULLUP);
  pinMode(PIN_BTN_BBPREL, INPUT_PULLUP);
  pinMode(PIN_BTN_BBLAP, INPUT_PULLUP);
  pinMode(PIN_BTN_BB1, INPUT_PULLUP);
  pinMode(PIN_BTN_BB2, INPUT_PULLUP);
  pinMode(PIN_BTN_RA1, INPUT_PULLUP);
  pinMode(PIN_BTN_RA2, INPUT_PULLUP);
  pinMode(PIN_BTN_FUEL, INPUT_PULLUP);
  pinMode(PIN_BTN_EXIT, INPUT_PULLUP);
  pinMode(PIN_BTN_TY_CLEAR, INPUT_PULLUP);
  pinMode(PIN_SW_TY_FR, INPUT_PULLUP);
  pinMode(PIN_SW_TY_RL, INPUT_PULLUP);
  pinMode(PIN_SW_VIEW_DN, INPUT_PULLUP);
  pinMode(PIN_SW_VIEW_UP, INPUT_PULLUP);
  pinMode(PIN_SW_O_R, INPUT_PULLUP);

  pinMode(PIN_LED_13, OUTPUT);
  pinMode(PIN_LED_PWM, OUTPUT);

  for( int i = 0; i < 8; i++ ) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH);
  }

  bb1Enc.write(0);
  bb2Enc.write(0);
  ra1Enc.write(0);
  ra2Enc.write(0);
  fuelEnc.write(0);
}

void normalOpJoystick() {
  // Update all the buttons.  There should not be any long
  // delays in loop(), so this runs repetitively at a rate
  // faster than the buttons could be pressed and released.
  updateButtons();

  handleButtonKey(&btnExit, KEY_EXIT);
  
  handleEncoderJoy(&bb1Enc, JOY_BTN_BB1_INC, JOY_BTN_BB1_DEC);
  handleEncoderJoy(&bb2Enc, JOY_BTN_BB2_INC, JOY_BTN_BB2_DEC);
  handleEncoderJoy(&ra1Enc, JOY_BTN_RA1_INC, JOY_BTN_RA1_DEC);
  handleEncoderJoy(&ra2Enc, JOY_BTN_RA2_INC, JOY_BTN_RA2_DEC);
  handleButtonJoy(&btnBb1, JOY_BTN_BB1_TOGGLE);
  handleButtonJoy(&btnBb2, JOY_BTN_BB2_TOGGLE);
  handleButtonJoy(&btnRa1, JOY_BTN_RA1_TOGGLE);
  handleButtonJoy(&btnRa2, JOY_BTN_RA2_TOGGLE);
  handleButtonJoy(&swViewUp, JOY_BTN_VIEW_UP);
  handleButtonJoy(&swViewDn, JOY_BTN_VIEW_DN);
  
  handleBlackBoxBtn(&btnBbPit, JOY_BTN_BB_PIT, PIN_R6);
  handleBlackBoxBtn(&btnBbCar, JOY_BTN_BB_CAR, PIN_R7);
  handleBlackBoxBtn(&btnBbFuel, JOY_BTN_BB_FUEL, PIN_R5);
  handleBlackBoxBtn(&btnBbTyre, JOY_BTN_BB_TYRE, PIN_R4);
  handleBlackBoxBtn(&btnBbPabs, JOY_BTN_BB_PABS, PIN_R2);
  handleBlackBoxBtn(&btnBbPrel, JOY_BTN_BB_PREL, PIN_R3);
  handleBlackBoxBtn(&btnBbLap, JOY_BTN_BB_LAP, PIN_R1);

  handleTyreButtons();
  handleFuel();
}


void loop() {
  normalOpJoystick();

  delay(LOOP_DELAY);
}
