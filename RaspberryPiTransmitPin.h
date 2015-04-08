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
	RaspberryPiTransmitPin(const int nTransmitPin);
	virtual ~RaspberryPiTransmitPin();

    int initialize();
    void pullPinLowForPeriodSync(const unsigned int nPulseLength);
    void pullPinHighForPeriodSync(const unsigned int nPulseLength);

private:
    void enableTransmit();
    void setPinLevel(const int nLevel);
    void pullPinToLevelForPeriodSync(const int nLevel, const unsigned int nPulseLength);

private:
    int nTransmitterPin;
};

#endif /* RASPBERRYPITRANSMITPIN_H_ */
