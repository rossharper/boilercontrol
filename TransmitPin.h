/*
 * TransmitPin.h
 *
 *  Created on: 8 Apr 2015
 *      Author: ross
 */

#ifndef TRANSMITPIN_H_
#define TRANSMITPIN_H_

class TransmitPin {
public:
	virtual ~TransmitPin(){};

    virtual void pullPinLowForPeriodSync(const unsigned int nPulseLength) = 0;
    virtual void pullPinHighForPeriodSync(const unsigned int nPulseLength) = 0;
};



#endif /* TRANSMITPIN_H_ */
