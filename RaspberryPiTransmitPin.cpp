/*
 * RaspberryPiTransmitPin.cpp
 *
 *  Created on: 8 Apr 2015
 *      Author: ross
 */

#include "RaspberryPiTransmitPin.h"

#include "Constants.h"

#include <stdio.h>
#include <wiringPi.h>

RaspberryPiTransmitPin::RaspberryPiTransmitPin(const int nTransmitPin, const int nNonRealtimeOffset) {
    this->init(nTransmitPin, nNonRealtimeOffset);
}

RaspberryPiTransmitPin::RaspberryPiTransmitPin(const int nTransmitPin) {
    this->init(nTransmitPin, nDefaultNonRealtimeOffset);
}

void RaspberryPiTransmitPin::init(const int nTransmitPin, const int nNonRealtimeOffset) {
    printf("RPi Transmit Pin: %d with offset: %d\n", nTransmitPin, nNonRealtimeOffset);
    this->nTransmitterPin = nTransmitterPin;
    this->nNonRealtimeOffset = nNonRealtimeOffset;
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
    if(nPulseLength > 0) {
        setPinLevel(nLevel);
        delayMicroseconds(nPulseLength - this->nNonRealtimeOffset);
    }
}

void RaspberryPiTransmitPin::pullPinLowForPeriodSync(const unsigned int nPulseLength) {
    pullPinToLevelForPeriodSync(LOW, nPulseLength);
}

void RaspberryPiTransmitPin::pullPinHighForPeriodSync(const unsigned int nPulseLength) {
    pullPinToLevelForPeriodSync(HIGH, nPulseLength);
}
