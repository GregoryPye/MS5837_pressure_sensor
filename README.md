# _MS5837 pressure sensor library_

## Purpose

This is a library to allow use of the MS65837 pressure sensor wih the ESP-IDF for ESP32.  It is based on the Arduino library at

https://github.com/senceryazici/BlueRobotics_MS5837_Library , but uses native ESP32 commands, including descheduling whilst coversions are in progress 

## Prerequisites

The MS5837 library depends on the following protocol libraries to communicate with the chip with ease: [ [I2Cbus] | [SPIbus] ].  
You must download the one according to the protocol you'll use and place within your components directory as well.

```
I2Cbus:  git clone https://github.com/natanaeljr/esp32-I2Cbus.git I2Cbus
SPIbus:  git clone https://github.com/natanaeljr/esp32-SPIbus.git SPIbus