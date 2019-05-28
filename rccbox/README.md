# Buttonbox for race control features

The box utilizes a Teensy 3.5 microcontroller because it has

* 5V tolerance on most pins
* enough I/O pins to map all the buttons and functions

All button / encoder actions are mapped to teensy joystick buttons exept the 
EXIT button which generates a ESC key press as a normal keyboard would.

The buttons, switches and encoder for tyre change and re-fuel should be mapped
to some pit macros in iRacing options. You need to define the following
macros:

* #cleartires* for the 'clear tyres' button
* #lf rf* for the up function of the 'change tyres' switch in ROAD mode
* #lr rr* for the down function of the 'change tyres' switch in ROAD mode
* #rf rr* for the up function of the 'change tyres' switch in OVAL mode
* #lr lf* for the down function of the 'change tyres' switch in OVAL mode
* #clearfuel* for the fuel encoder push function

The LED's for tyre change and re-fuel during pit service are triggered by the
corresponding switches and/or encoders. If you use the buttonbox in conjunction
with the [ir2mqtt](../ir2mqtt/README.md) application, the lights can reflect the
pit service status of tyres and fuel based on the current telemetry data which is
much more accurate - especially in team races where the crew chief is typically
setting the pit service actions.

## Wiring diagram

to be done

