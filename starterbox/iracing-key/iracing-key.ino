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

// Create Bounce objects for each button.  The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.
// 10 = 10 ms debounce time
Bounce button0 = Bounce(0, 10);     // Ignition switch
Bounce button1 = Bounce(1, 10);     // Engine starter
Bounce button2 = Bounce(2, 10);     // ACC1 switch
Bounce button3 = Bounce(3, 10);     // ACC2 switch
Bounce button4 = Bounce(4, 10);     // ENG push
Bounce button5 = Bounce(17, 10);    // ABS push
Bounce button6 = Bounce(18, 10);    // TCR push

Encoder eng(5, 16);
Encoder abs(6, 15);
Encoder tcr(7, 14);

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
  pinMode(17, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);

  tcr.write(0);
}


void loop() {
  // Update all the buttons.  There should not be any long
  // delays in loop(), so this runs repetitively at a rate
  // faster than the buttons could be pressed and released.
  button0.update();
  button1.update();
  button2.update();
  button3.update();
  button4.update();
  button5.update();
  button6.update();
//  button7.update();
//  button8.update();
//  button9.update();

  long newTcr, newAbs, newEng;

  // Check each button for "falling" edge.
  // Type a message on the Keyboard when each button presses
  // Update the Joystick buttons only upon changes.
  // falling = high (not pressed - voltage from pullup resistor)
  //           to low (pressed - button connects pin to ground)

  // Ignition Switch
  if (button0.fallingEdge()) {
    Keyboard.print("i");
  }
  if( button0.risingEdge()) {
    Keyboard.print("i");
  }

  // Engine start button - continously
  if (button1.fallingEdge()) {
    Keyboard.press(KEY_S);
  }
  if( button1.risingEdge()) {
    Keyboard.release(KEY_S);
  }

  // ACC1 switch - pit limiter
  if (button2.fallingEdge()) {
    Keyboard.print("p");
  }
  if( button2.risingEdge()) {
    Keyboard.print("p");
  }

  // ACC2 switch - voice chat mute
  if (button3.fallingEdge()) {
    Keyboard.print("q");
  }
  if( button3.risingEdge()) {
    Keyboard.print("q");
  }

  // ACC2 switch - voice chat mute
  if (button4.fallingEdge()) {
    Keyboard.press(KEY_Q);
  }
  if( button4.risingEdge()) {
    Keyboard.release(KEY_Q);
  }

  newTcr = tcr.read();
  if(newTcr < - 2) {
    Keyboard.print("t");
  } else if( newTcr > 2 ) {
    Keyboard.print("T");
  }
  tcr.write(0);
  
  delay(50);
}
