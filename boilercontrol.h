#ifndef BOILERCONTROL_H_
#define BOILERCONTROL_H_

static const unsigned int nBitsPerPacket = 33;

class TransmitPin;

struct Bit {
    unsigned int highLengthMicros;
    unsigned int lowLengthMicros;
};

struct Packet {
    Bit preambleBit;
    unsigned int nPreambleBits;
    Bit onBit;
    Bit offBit;
    unsigned int dataBits[25];
};

struct ControlPackets {
    unsigned int nPacketRepeats;
    Packet onPacket;
    Packet offPacket;
};

class BoilerControl {

public: 
    BoilerControl(TransmitPin *transmitPin);
    virtual ~BoilerControl();

    void sendOnSignal();
    void sendOffSignal();

private:
//    void sendPackets(const int packets[][nBitsPerPacket]);
//    void sendPacket(const int packet[], const unsigned int nPostPacketDelay);
//    void sendTxStart();
//    void send1();
//    void send0();
//    void sendPulse(const unsigned int nPulselength);
    void sendPackets(Packet packet, unsigned int nRepeats);
    void sendPacket(Packet packet);
    void sendPacketPreamble(Bit preambleBit, unsigned int nPreambleBits);
    void sendBit(Bit bit);

private:
    ControlPackets controlPackets;
    TransmitPin* transmitPin;
};

#endif /* BOILERCONTROL_H_ */
