# Alternative Micros for the UKMARSBot

Want to use a different micro for UKMARSBot? 

Information collected, extended and edited by Rob Probin, August 2023 to Jan 2024.

Contributions from many UKMARS members. 

http://ukmars.org

https://github.com/ukmars/

Suggestions for enhancement and corrections welcome.

## Introduction

The original design of the UKMARSbot was based on a Arduino Nano. This 
development board uses a ATMega328P microcontroller. 

While there were good reasons for choosing this development board but its
small memory and features have been questioned against more modern
alternatives. 

Specfically the Arduino Nano board:
 * has a small form factor,
 * is fairly cost effective, 
 * is well documented both using as an Arduino device and as a standalone 
microcontroller. 
 * has availability of third-party clones of the development board (and even the 
microcontroller itself has (somewhat upgraded) clone),
 * has an on-board regulator,
 * has an on-board USB to serial converter,
 * can be programmed without special equipment.
 * has good support for C, C++ and Forth programming languages.  


## What are the Easy Update Options

Since then, robot builders have successfully used several other 
microcontroller boards with more modern processors.  

Currently three are documented here in some detail, and these specifically 
fit into the same pin-out and form factor of the Arduino Nano, with only 
minimal changes. These are therefore the easiest to implement. 

 * Cytron Maker Nano RP2040
 * Arduino Nano RP2040 Connect
 * Arduino Nano 33 BLE

The RP2040 boards give the option of Micropython. The Nano 33 BLE board is also interesting. 


## Other Board Options

These are not the only options. Here are some details for other options:

You might also want to review the recording of a presentation by Peter Harrison discusion on 
various alternatives: https://youtu.be/_E6mRQq4exo

Raspberry Pico UKMARSbot https://ukmars.org/2021/02/a-raspberry-pi-pico-based-ukmarsbot/

Alternative Processors for UKMARSBOT https://ukmars.org/2020/12/alternative-processors-for-ukmarsbot/

Of course, the choice is not limited if you are willing to invest the time. Please contact us if 
you have detailed descriptions of the changes for other options - we'd love to hear from you!


## REFERENCES

Originally these instructions were hosted at: https://github.com/robzed/UKMARSbot_RPi_Pico_Adapter

 
