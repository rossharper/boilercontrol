#! /bin/bash
/usr/local/bin/gpio-admin export 17
echo out > /sys/class/gpio/gpio17/direction
exit 0
