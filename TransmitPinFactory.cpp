//
// Created by Ross Harper on 08/04/2015.
//

#include "TransmitPinFactory.h"

#include <stdio.h>

#ifdef RASPBERRY_PI
#include "RaspberryPiTransmitPin.h"

TransmitPin* TransmitPinFactory::create(int nTransmitPin) {
    return TransmitPinFactory::create(nTransmitPin, nDefaultNonRealtimeOffset);
}

TransmitPin* TransmitPinFactory::create(int nTransmitPin, int nNonRealtimeOffset) {
    printf("Constructing RaspberryPi TransmitPin\n");

    RaspberryPiTransmitPin* transmitPin = new RaspberryPiTransmitPin(nTransmitPin, nNonRealtimeOffset);

    if(transmitPin->initialize() == 0){
        delete transmitPin;
        transmitPin = 0;
    }

    return transmitPin;
}
#else

#include "StubTransmitPin.h"

TransmitPin* TransmitPinFactory::create(int nTransmitPin) {
    return TransmitPinFactory::create(nTransmitPin, 0);
}

TransmitPin* TransmitPinFactory::create(int /*nTransmitPin*/, int nNonRealtimeOffset) {
    printf("Constructing STUB TransmitPin\n");
    return new StubTransmitPin();
}

#endif
