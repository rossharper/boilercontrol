//
// Created by Ross Harper on 08/04/2015.
//

#include "TransmitPinFactory.h"

#ifdef RASPBERRY_PI
#include "RaspberryPiTransmitPin.h"

TransmitPin* TransmitPinFactory::create(int nTransmitPin) {
    RaspberryPiTransmitPin* transmitPin = new RaspberryPiTransmitPin(nTransmitPin);

    if(transmitPin->initialize() == 0){
        delete transmitPin;
        transmitPin = 0;
    }

    return transmitPin;
}
#else

#include "StubTransmitPin.h"

TransmitPin* TransmitPinFactory::create(int /*nTransmitPin*/) {
    return new StubTransmitPin();
}

#endif
