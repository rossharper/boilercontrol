/*
 * RaspberryPiPin.h
 *
 *  Created on: 8 Apr 2015
 *      Author: ross
 */

#ifndef RASPBERRYPITRANSMITPIN_H_
#define RASPBERRYPITRANSMITPIN_H_

#include "TransmitPin.h"

class RaspberryPiTransmitPin : public TransmitPin {
public:
	RaspberryPiTransmitPin(const unsigned int nTransmitPin);
	virtual ~RaspberryPiTransmitPin();

    void pullPinLowForPeriodSync(const unsigned int nPulseLength);
    void pullPinHighForPeriodSync(const unsigned int nPulseLength);

private:
    void enableTransmit();
    void delayForPeriod(const unsigned int nDelayMicroseconds);
    void setPinLevel(const int nLevel);
    void pullPinToLevelForPeriodSync(const int nLevel, const unsigned int nPulseLength);

private:
    unsigned int nTransmitterPin;
};

#endif /* RASPBERRYPITRANSMITPIN_H_ */
