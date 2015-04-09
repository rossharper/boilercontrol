/*
 * RaspberryPiPin.cpp
 *
 *  Created on: 8 Apr 2015
 *      Author: ross
 */

#include "RaspberryPiTransmitPin.h"

#include <stdio.h>
#include <wiringPi.h>

static const unsigned int nNonRealtimeOffset = 90;

RaspberryPiTransmitPin::RaspberryPiTransmitPin(const int nTransmitPin) {
	printf("RPi Transmit Pin: %d with offset: %d", nTransmitPin, nNonRealtimeOffset);
    this->nTransmitterPin = nTransmitterPin;
    this->enableTransmit();
}

RaspberryPiTransmitPin::~RaspberryPiTransmitPin() {

}

int RaspberryPiTransmitPin::initialize() {
    return (wiringPiSetup() != 1);
}

void RaspberryPiTransmitPin::enableTransmit() {
    pinMode(this->nTransmitterPin, OUTPUT);
}

void RaspberryPiTransmitPin::setPinLevel(const int nLevel) {
    digitalWrite(this->nTransmitterPin, nLevel);
}

void RaspberryPiTransmitPin::pullPinToLevelForPeriodSync(const int nLevel, const unsigned int nPulseLength) {
    setPinLevel(nLevel);
    delayMicroseconds(nPulseLength - nNonRealtimeOffset);
}

void RaspberryPiTransmitPin::pullPinLowForPeriodSync(const unsigned int nPulseLength) {
    pullPinToLevelForPeriodSync(LOW, nPulseLength);
}

void RaspberryPiTransmitPin::pullPinHighForPeriodSync(const unsigned int nPulseLength) {
    pullPinToLevelForPeriodSync(HIGH, nPulseLength);
}
