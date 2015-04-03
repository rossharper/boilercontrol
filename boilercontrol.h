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
    void sendPacket(const int packet[]);
    void sendRxStart();
    void send1();
    void send0();
    void sendPulse(const unsigned int nPulselength);

private:
    unsigned int nTransmitterPin;
};
