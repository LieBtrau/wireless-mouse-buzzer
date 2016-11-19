# wireless-mouse-buzzer
A buzzer that alerts the user that the wireless mouse is still on while the computer is turned off.

An ATTINY9-TSHR controls a piezo buzzer.

Using a function generator it has been found that the buzzer sounds the loudest at 950Hz.  
# Programming using Atmel avrisp

| TPI signal name |avrisp pin nr. | attiny 9 pin nr |
|-----------------|---------------|-----------------|
| DATA            |1              | 1               |
| VTG             |2              | 5               |
| CLOCK           |3              | 3               |
| RESET           |5              | 6               |
| GND             |6              | 2               |

* Remark that the avrisp follows the pin number scheme of a pin header.  The attiny9 follows the pin number scheme of an IC.
* Programming voltage of the attiny9 is 5V.
* Power the avrisp directly from your PC, not through some cheap USB-hub.

# Connections
The mouse drives an LED when the wireless mouse is still on, but the computer is switched off.  The LED and the serial resistor are replaced by the circuit described below.  
The buzzer is connected with two GPIO's of the MCU to drive it in a H-bridge configuration.

* Pin 1 connected to one side of the piezo element.
* Pin 3 connected to a series resistor that connects to the other side of the piezo element.  

With a 2K2 resistor, the signal is still audible when powering the ATTINY at 1V8.  The series resistor could be decreased until the maximum output current for the ATTINY is reached.  Let's choose an 100ohm resistor.  This limits the pin current to 20mA, which is safely below the maximum 40mA per pin.
