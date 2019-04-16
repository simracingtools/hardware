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

// Create Bounce objects for each button.  The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.
Bounce button0 = Bounce(0, 10);
Bounce button1 = Bounce(1, 10);  // 10 = 10 ms debounce time
Bounce button2 = Bounce(2, 10);  // which is appropriate for
Bounce button3 = Bounce(3, 10);  // most mechanical pushbuttons
Bounce button4 = Bounce(4, 10);
Bounce button5 = Bounce(5, 10);  // if a button is too "sensitive"
Bounce button6 = Bounce(6, 10);  // to rapid touch, you can
Bounce button7 = Bounce(7, 10);  // increase this time.
Bounce button8 = Bounce(8, 10);
Bounce button9 = Bounce(9, 10);

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
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);  // Teensy++ LED, may need 1k resistor pullup
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
}

boolean btn1 = false;
boolean btn3 = false;
boolean btn4 = false;

void loop() {
  // Update all the buttons.  There should not be any long
  // delays in loop(), so this runs repetitively at a rate
  // faster than the buttons could be pressed and released.
  button0.update();
  button1.update();
  button2.update();
  button3.update();
//  button4.update();
//  button5.update();
//  button6.update();
//  button7.update();
//  button8.update();
//  button9.update();

  // Check each button for "falling" edge.
  // Type a message on the Keyboard when each button presses
  // Update the Joystick buttons only upon changes.
  // falling = high (not pressed - voltage from pullup resistor)
  //           to low (pressed - button connects pin to ground)

  // Ignition Switch
  if( btn1 ) {
    Joystick.button(1, 0);
    btn1 = false;
  }
  if (button0.fallingEdge()) {
    //Keyboard.print("i");
    Joystick.button(1, 1);
    btn1 = true;
  }
  if( button0.risingEdge()) {
    //Keyboard.print("i");
    Joystick.button(1, 1);
    btn1 = true;
  }
 
  // Engine start button - continously
  if (button1.fallingEdge()) {
    Joystick.button(2, 1);
  }
  if( button1.risingEdge()) {
    Joystick.button(2, 0);
  }

  // ACC1 switch
  if( btn3 ) {
    Joystick.button(3, 0);
    btn3 = false;
  }
  if (button2.fallingEdge()) {
    Joystick.button(3, 1);
    btn3 = true;
  }
  if( button2.risingEdge()) {
    Joystick.button(3, 1);
    btn3 = true;
  }

  // ACC2 switch
  if( btn4 ) {
    Joystick.button(4, 0);
    btn4 = false;
  }
  if (button3.fallingEdge()) {
    Joystick.button(4, 1);
    btn4 = true;
  }
  if( button3.risingEdge()) {
    Joystick.button(4, 1);
    btn4 = true;
  }

  delay(100);
}
