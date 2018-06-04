# Simple Radio Node

## About
A simple NodeMCU based internet radio receiver dedicated to my family. It is hardcoded to a single station. Just turn on and listen.

## Parts List
- ESP8266 NodeMCU
- VS1053 MP3 Decoder Breakout Board
- PAM8304 Class-D Amplifier

## Wiring

| VS1053  | ESP8266 |  Other   |
|---------|---------|----------|
|   SCK   |   D5    |    -     |
|   MISO  |   D6    |    -     |
|   MOSI  |   D7    |    -     |
|   XRST  |    -    |    -     |
|   CS    |   D1    |    -     |
|   DCS   |   D0    |    -     |
|   DREQ  |   D3    |    -     |
|   5V    |    -    |   VCC    |
|   GND   |    -    |   GND    |

## Dependencies
- VS1053 library by baldram (https://github.com/baldram/ESP_VS1053_Library)

## Instructions:
-Build the hardware
-Set the station in this file
-Upload the program

## IDE Settings (Tools):
-IwIP Variant: v1.4 Higher Bandwidth
-CPU Frequency: 160Hz
