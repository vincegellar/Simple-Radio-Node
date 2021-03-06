# Simple Radio Node

## About
A simple ESP8266 NodeMCU and VS1053 based internet radio receiver dedicated to my family. It is hardcoded to a single station. Just turn on and listen.

## Parts List
- ESP8266 NodeMCU
- VS1053 MP3 Decoder Breakout Board
- PAM8304 Class-D Amplifier
- 2x 3W 4Ohm or 8Ohm Speakers
- 5V 3A Power Supply
- 47uF Capacitor
- Switch
- 47k Ohm Resistor
- 10k Ohm Resistor
- 10k Trim Potentiometer
- Wire

## Dependencies
- VS1053 library by baldram (https://github.com/baldram/ESP_VS1053_Library)

## Instructions:
- Build the hardware
- Set the station
- Set your Wi-Fi SSID and password
- Upload the program

## IDE Settings (Tools):
- IwIP Variant: v2.0 Higher Bandwidth
- CPU Frequency: 160Hz

## Wiring
| VS1053  | ESP8266 |  Other   |
|---------|---------|----------|
|   SCK   |   D5    |    -     |
|   MISO  |   D6    |    -     |
|   MOSI  |   D7    |    -     |
|   RST   |    -    |    -     |
|   CS    |   D1    |    -     |
|   DCS   |   D0    |    -     |
|   DREQ  |   D3    |    -     |
|   5V    |    -    |   VCC    |
|   GND   |    -    |   GND    |

**_To avoid noise caused by the power supply and the jack connector creating a ground loop, solder a 47uF capacitor onto the PAM8403's VREF pin, and connect it to the jack connector's ground._**

**_The volume control uses a 47k Ohm resistor from the 3.3V line, then a 10k Ohm resistor to the NodeMCU's ground._**

![Schematic](https://github.com/vincegellar/Simple-Radio-Node/blob/master/Images/sr_node.png)

## License:

Simple Radio Node: a single station easy to use web radio.
    Copyright (C) 2018  Vince Gellár (gellar.vince@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
