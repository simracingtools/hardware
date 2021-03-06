# Buttonbox for engine start and control

## Motivation

The idea came to me when I saw [this Panel on Amazon](https://www.amazon.de/dp/B01BV9CWW2/?coliid=ILLJIW41VWR2C&colid=2JV752ZE9GTFC&psc=0&ref_=lv_ov_lig_dp_it).

Then I saw similar panel on [aliexpress.com](https://de.aliexpress.com/item/12V-20A-Carbon-Faser-Sim-Racing-Auto-Z-ndung-Schalter-Ersatz-Panel-Push-Start-anzeige-licht/32913185496.html) and ordered it and started to [build](Making.md)

## Functions

<img src="images/small/BoxDecoratedFinal.jpg" alt="The Result" width="600px"/>

The box can operate as a keyboard or joystick. I prefer the keyboard variant on iRacing but it depends on your
desires and prefered racing simulation which mode fits best.

[Short Reference](Reference.md)

### Ignition safety switch

The ignition switch is mapped to a single "i" character in keyboard mode every time it's operated.

A short single button 1 press is generated in joystick mode.

So be sure that your simulation is consistent with it's current state. If I forget to switch it off before a new 
simulation starts, then turning off ignition on the box turns ignition on in the simulation ... you know what I mean ?! ;-)

### Engine starter

The engine starter button behaves like the "s" key on the keyboard. If you hold it down it repeats the key as a 
keyboard would do.

Button 2 is used in joystick mode.

### Pit limiter switch

The pit limiter switch is mapped to a single "p" character every time it's operated.

A short single button 3 press is generated in joystick mode.

### Traction control switch

The TC switch changes the characters generated by the TC encoder. This is especially made for the Ferrari 488 GTE in
iRacing which has modeled two different traction control settings.

### Traction control encoder

The encoder in keyboard mode produces a series of "1" characters when turned left (-) and "2" characters when turned right (+) if the 
TC switch is in TC1 position. With TC switch in TC2 position the encoder produces the characters "3" when turned 
left (-) and "4" when turned right.

A push on the encoder knob produces the character "q" as a keyboard would do.

In joystick mode the buttons 9 (-) and 10 (+) are used for TC1, 7 (-) and 8 (+) for TC2. Button 4 is used when the
encoder is pushed.

### ABS encoder

The encoder produces a series of "5" characters when turned left (-) and "6" characters when turned right (+). 
A push on the encoder knob produces the character "a" as a keyboard would do.

In joystick mode the buttons 10 (-) and 11 (+) are used. Button 9 is used when the encoder is pushed.


### Engine mode encoder

The encoder supports two settings which can be toggled by a push on the encoder knob. The two LED's on its left
indicate the selected setting (fuel mix or throttle shaping).

With fuel mix selected the encoder produces a series of "7" characters when turned left (-) and "8" characters when 
turned right (+). If throttle shaping is selected the encoder produces a series of "9" characters when turned left (-) 
and "0" characters when turned right (+).

In joystick mode the buttons 12 (-) and 13 (+) are used for fuel mix, 14 (-) and 15 (+) for throttle shaping.

## Configuration

### LED brightness, encoder sensitivity and operation mode

LED brightness and encoder sensitivity are configurable. To enter configuration mode press ENG and ABS encoder while 
ignition switch is off. Both LED light up to indicate configuration mode and the red one blinks some times 
according to the current encoder sensitivity setting.

You can now set LED brightness with the ENG encoder. The LED brightness will change immediately.

The encoder sensitivity is set by turning the ABS encoder. A push on ABS encoder will cause the blue led to blink 
various times. The more the LED blinks, the less the encoder sensitivity.

A push on the TC encoder toggles between keyboard an joystick operation mode. Two blinks of the blue led indicates
joystick mode, two blinks of the red led indicates keyboard operation mode.

To leave config mode switch ignition on.

The configuration is written into non volatile memory so it will remain intact over a power cycle.

### Key/Joystick button mappings

If you need to change any of the characters generated or used joystick buttons, you have to modify the 
[config.h](https://github.com/robbyb67/simracing/tree/master/starterbox/iracing-key/config.h) file and reprogram the
Teensy controller. As the used Teensy 2.0 does not support an external "Program" button you may have to open the box
if the loader application is not able to put the Teensy into bootloader mode.

By that means you should be able to easily adapt the functions to any other racing simulation.

