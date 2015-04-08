#ifndef BOILERCONTROL_H_
#define BOILERCONTROL_H_

#include <wiringPi.h>

static const unsigned int nBitsPerPacket = 33;

class BoilerControl {

public: 
    BoilerControl(int nTransmitterPin);

    void sendOnSignal();
    void sendOffSignal();

private:
    void enableTransmit();
    void sendPackets(const int packets[][nBitsPerPacket]);
    void sendPacket(const int packet[], const unsigned int nPostPacketDelay);
    void sendTxStart();
    void send1();
    void send0();
    void sendPulse(const unsigned int nPulselength);
    void delayForPeriod(const unsigned int nDelayMicroseconds);
    void setPinLevel(const int nLevel);
    void pullPinToLevelForPeriodSync(const int nLevel, const unsigned int nPulseLength);
    void pullPinLowForPeriodSync(const unsigned int nPulseLength);
    void pullPinHighForPeriodSync(const unsigned int nPulseLength);

private:
    unsigned int nTransmitterPin;
};

#endif BOILERCONTROL_H_
