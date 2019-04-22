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

void setup() {
  pinMode(0, INPUT_PULLUP);

  pinMode(16, OUTPUT);
  digitalWrite(16, HIGH);
  pinMode(17, OUTPUT);
  digitalWrite(17, HIGH);
  pinMode(18, OUTPUT);
  digitalWrite(18, HIGH);
  pinMode(19, OUTPUT);
  digitalWrite(19, HIGH);
  pinMode(20, OUTPUT);
  digitalWrite(20, HIGH);
  pinMode(21, OUTPUT);
  digitalWrite(21, HIGH);
  pinMode(22, OUTPUT);
  digitalWrite(22, HIGH);
  pinMode(23, OUTPUT);
  digitalWrite(23, HIGH);
}

int pin = 16;
void loop() {
  // Update all the buttons.  There should not be any long
  // delays in loop(), so this runs repetitively at a rate
  // faster than the buttons could be pressed and released.
  button0.update();

  if (button0.fallingEdge()) {
    if( pin - 1 < 16 ) {
      digitalWrite(23, HIGH);
    } else {
      digitalWrite(pin - 1, HIGH);
    }
    digitalWrite(pin, LOW);
    pin++;
    if( pin > 23 ) {
      pin = 16;
    }
  }
  if( button0.risingEdge()) {
//    digitalWrite(pin, HIGH);
//    pin++;
//    if( pin > 23 ) {
//      pin = 16;
//    }  
  }

  delay(50);
}
