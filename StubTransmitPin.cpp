//
// Created by Ross Harper on 08/04/2015.
//

#include "StubTransmitPin.h"

#include <stdio.h>

void StubTransmitPin::pullPinLowForPeriodSync(const unsigned int nPulseLength) {
    printf("L %d - ", nPulseLength);
}

void StubTransmitPin::pullPinHighForPeriodSync(const unsigned int nPulseLength) {
    printf("H %d - ", nPulseLength);
}

StubTransmitPin::StubTransmitPin() {
}

StubTransmitPin::~StubTransmitPin() {
}
