//
// Created by Ross Harper on 08/04/2015.
//

#ifndef BOILERCONTROL_TRANSMITPINFACTORY_H
#define BOILERCONTROL_TRANSMITPINFACTORY_H

class TransmitPin;

class TransmitPinFactory {
public:
    static TransmitPin* create(int nTransmitPin);
};


#endif //BOILERCONTROL_TRANSMITPINFACTORY_H
