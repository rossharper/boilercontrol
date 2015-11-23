# boilercontrol

## Overview

This is a (little bit hacky) utility for sending "call for heat" ON and OFF messages to my Siemens RCR10/433 receiver boiler control relay.

*NOTE*: The ON and OFF packets herein are specific to my receiver: they probably contain some ID that was exchanged during the "learn" mode pairing between receiver and thermostat.

Currently configured to use WiringPi PIN 0 (GPIO 17) to transmit on (should be connected to DATA pin of a 433Mhz transmitter).

## Usage

To call for heat (turn boiler ON):

    sudo ./callforheat 1

To cancel call for heat (turn boiler OFF):

    sudo ./callforheat 0

## Dependencies

[WiringPi](http://wiringpi.com/)

## Build

To build a version with the transmit pin control stubbed:

    make

To build for the Raspberry PI:

    make PLATFORM=pi

## More Information

A blog post I made in response to a question about this project:

http://rossharper.net/2015/11/decoding-a-siemens-rcr10433-thermostat-signal-to-control-a-boiler-from-a-raspberry-pi/
