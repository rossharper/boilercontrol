//
// Created by Ross Harper on 08/04/2015.
//

#ifndef BOILERCONTROL_STUBTRANSMITPIN_H
#define BOILERCONTROL_STUBTRANSMITPIN_H

#include "TransmitPin.h"

class StubTransmitPin : public TransmitPin {
public:
    StubTransmitPin();
    virtual ~StubTransmitPin();

    void pullPinLowForPeriodSync(const unsigned int nPulseLength);
    void pullPinHighForPeriodSync(const unsigned int nPulseLength);
};


#endif //BOILERCONTROL_STUBTRANSMITPIN_H
