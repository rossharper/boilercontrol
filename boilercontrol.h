#ifndef BOILERCONTROL_H_
#define BOILERCONTROL_H_

static const unsigned int nBitsPerPacket = 33;

class TransmitPin;

class BoilerControl {

public: 
    BoilerControl(int nTransmitterPin);
    virtual ~BoilerControl();

    void sendOnSignal();
    void sendOffSignal();

private:
    void sendPackets(const int packets[][nBitsPerPacket]);
    void sendPacket(const int packet[], const unsigned int nPostPacketDelay);
    void sendTxStart();
    void send1();
    void send0();
    void sendPulse(const unsigned int nPulselength);

private:
    TransmitPin* transmitPin;
};

#endif /* BOILERCONTROL_H_ */
