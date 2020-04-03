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
    unsigned int postPacketDelay;
};

class BoilerControl {

public: 
    BoilerControl(TransmitPin *transmitPin);
    virtual ~BoilerControl();

    void sendOnSignal();
    void sendOffSignal();

private:
    void sendPackets(Packet packet, unsigned int nRepeats, unsigned int postPacketDelayMillis);
    void sendPacket(Packet packet);
    void sendPacketPreamble(Bit preambleBit, unsigned int nPreambleBits);
    void sendBit(Bit bit);
    void sendPostPacketDelay(const unsigned postPacketDelayMillis);

private:
    ControlPackets controlPackets;
    TransmitPin* transmitPin;
};

#endif /* BOILERCONTROL_H_ */
