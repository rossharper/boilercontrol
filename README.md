# boilercontrol
Very hacky attempt at sending boiler control codes.

By subtracting an arbitrary 90µs from each pulse length, I seem to have got around the non-realtime nature of Linux that was causing the pulses to be too long. And it only bloody works!
