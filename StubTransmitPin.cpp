//
// Created by Ross Harper on 08/04/2015.
//

#include <iostream>
#include "StubTransmitPin.h"

void StubTransmitPin::pullPinLowForPeriodSync(const unsigned int nPulseLength) {
    std::cout << "H " << std::to_string(nPulseLength) << std::endl;
}

void StubTransmitPin::pullPinHighForPeriodSync(const unsigned int nPulseLength) {
    std::cout << "L " << std::to_string(nPulseLength) << std::endl;
}

StubTransmitPin::StubTransmitPin() {
}

StubTransmitPin::~StubTransmitPin() {
}
