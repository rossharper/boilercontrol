//
// Created by Ross Harper on 08/04/2015.
//

#include "TransmitPinFactory.h"
#include "RaspberryPiTransmitPin.h"

TransmitPin* TransmitPinFactory::create(int nTransmitPin) {
    RaspberryPiTransmitPin* transmitPin = new RaspberryPiTransmitPin(nTransmitPin);

    if(transmitPin->initialize() == 0){
        delete transmitPin;
        transmitPin = 0;
    }

    return transmitPin;
}
