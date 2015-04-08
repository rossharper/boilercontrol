/*
 * RaspberryPiPin.cpp
 *
 *  Created on: 8 Apr 2015
 *      Author: ross
 */

#include "RaspberryPiTransmitPin.h"

#include <wiringPi.h>

static const unsigned int nNonRealtimeOffset = 90;

RaspberryPiTransmitPin::RaspberryPiTransmitPin(const unsigned int nTransmitPin) {
	this->nTransmitterPin = nTransmitterPin;

}

RaspberryPiTransmitPin::~RaspberryPiTransmitPin() {

}

void RaspberryPiTransmitPin::enableTransmit() {
    pinMode(this->nTransmitterPin, OUTPUT);
}

void RaspberryPiTransmitPin::delayForPeriod(const unsigned int nDelayMicroseconds) {
    delayMicroseconds(nDelayMicroseconds - nNonRealtimeOffset);
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
