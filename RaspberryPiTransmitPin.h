/*
 * RaspberryPiTransmitPin.h
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
	RaspberryPiTransmitPin(const int nTransmitPin, const int nNonRealtimeOffset);
	virtual ~RaspberryPiTransmitPin();

    int initialize();
    void pullPinLowForPeriodSync(const unsigned int nPulseLength);
    void pullPinHighForPeriodSync(const unsigned int nPulseLength);

private:
    void init(const int nTransmitPin, const int nNonRealtimeOffset);
    void enableTransmit();
    void setPinLevel(const int nLevel);
    void pullPinToLevelForPeriodSync(const int nLevel, const unsigned int nPulseLength);

private:
    int nTransmitterPin;
    int nNonRealtimeOffset;
};

#endif /* RASPBERRYPITRANSMITPIN_H_ */
