# NotSoTactileMACRO

Atmega32u4 based macro pad with rotary encoders and Cherry MX switches.

<p align="center">
  <img width="577" height="450" src="https://github.com/Cipulot/NotSoTactileMACRO/blob/main/media/NoSoTactileMACRO.jpg">
</p>

This final prototype of the NotSoTactileMACRO. In this configuration there are 12 MX switches + 1 button from the rotary encoder on the bottom. The button for the encoder in the middle is used for resetting the Arduino Micro board.

The original implementation of the software was done using the base Arduino Keyboard library, later replaced by the [HID-Project](https://github.com/NicoHood/HID).

## Design

As for the majority of this kind of projects a matrix is implemented for the switches. In particular, to reduce component usage, the internal pull up system has being used for the pins.

Here's a picture of the schematic for the board:
<p align="center">
 <img width="577" height="450" src="https://github.com/Cipulot/NotSoTactileMACRO/blob/main/media/Schematic.png">
</p>

## Features

