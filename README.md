# boilercontrol

## Overview

This is a (little bit hacky) utility for sending "call for heat" ON and OFF messages to my Siemens RCR10/433 receiver boiler control relay. (Note: the codes have since been updated to a generic 433MHz thermostat)

*NOTE*: The ON and OFF packets herein are specific to my receiver: they probably contain some ID that was exchanged during the "learn" mode pairing between receiver and thermostat.

Currently configured to use WiringPi PIN 0 (GPIO 17) to transmit on (should be connected to DATA pin of a 433Mhz transmitter). GPIO pin 17 should be configured for export with `gpio` which will make changes to ```/sys/class/gpio```.

```
gpio export 17 out
```

NOTE: the install script will setup an init script (debian-compatible) that exports GPIO 17 with direction=out.

## Usage

```
    callforheat 0 [offset] // Call for heat OFF
    callforheat 1 [offset] // Call for heat ON

    [offset] Microseconds to reduce pulse lengths by. Default: 90
             also set via CALLFORHEAT_OFFSET environment variable.
```

To call for heat (turn boiler ON):

    callforheat 1

To cancel call for heat (turn boiler OFF):

    callforheat 0

To call for heat with realtime offset increased to 100us:

    callforheat 1 100
```

```

## Dependencies

[WiringPi](http://wiringpi.com/)

```sudo apt-get install wiringpi```

## Build

To build a version with the transmit pin control stubbed:

    make

To build for the Raspberry PI:

    make PLATFORM=pi

To install on the Raspberry PI:

    make install PLATFORM=pi

To uninstall

    make uninstall PLATFORM=pi

## More Information

A blog post I made in response to a question about this project:

http://rossharper.net/2015/11/decoding-a-siemens-rcr10433-thermostat-signal-to-control-a-boiler-from-a-raspberry-pi/
