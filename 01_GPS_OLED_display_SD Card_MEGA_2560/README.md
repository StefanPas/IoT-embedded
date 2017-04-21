### The project is divided into two parts:

1. Development of a hardware prototype combining GPS, OLED display, SD cards module and arduino MEGA 2560, plus a 12V lithium battery. This prototype can show the GPS data on the OLED display and store satellite readings into a csv file. 

2. Python/Django platform alowing upload of the csv file, which is stored into a MogoDB. The system shows all routes based on the date taken from the csv files. Each route can be visualized by google map.

### COMPONENTS USED IN THIS PROJECT

1. NEO 6M GPS 

GPS modules NEO-6M, 3V-5V power supply Universal
Model: GY-GPS6MV2
Destined module with ceramic antenna, signal super
Save the configuration parameter data EEPROM Down
With data backup battery
There are LED signal indicator
Antenna size 25 * 25mm
Module size 25mm * 35mm
Installation aperture 3mm
Default Baud Rate: 9600
Compatible with various flight control modules that provide GPS computer test software
PINS: RX, TX, GND, VCC

The GPS receiver uses serial communication protocol to communicate with the arduino MEGA board. The Arduino Mega has three serial ports: Serial1 on pins 19 (RX) and 18 (TX), Serial2 on pins 17 (RX) and 16 (TX), Serial3 on pins 15 (RX) and 14 (TX). For this example the connection is set on Serial1, pins 19 (RX) and 18 (TX).


2. OLED Display
   
0.96 inch 128X64
Mono blue color
power supply  3 ~ 5.5 V 
PINS: GND, VCC, SCL, SDA

This module works with I2C communication protocol which requires two signal wires for sending/receiving the data - the serial data pin SDA (data line) and serial clock pin SCL (clock line). To make the device working are needed the device address and data rate for serial data transmission.


3. SD CARD

3.3v / 5v power supply 
3.3v / 5v I/0 operation level compatile
strandard 0.1" x 6 pin headers breakout
supprort SD/micro SD 
PINS: CS (SS), DI (MOSI), DO (MISO), CLK (SCK), GND (G), VCC (+)

The communication between the MEGA microcontroller and the SD card is based on SPI (Serial Peripheral Interface). The MEGA board pinout connections are: 50 (DO), 51 (DI), 52 (CLK), 53 (CS).

4. DC 168 - 12V lithium battery

Capacity: 1800mAh 
Input Voltage : 12.6V DC;
Imput connector head : 5.5" DC female 
Output voltage  : 12V DC
Output current:  2A
Output connector head : 5.5" DC male.

