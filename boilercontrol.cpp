#include "boilercontrol.h"

#include "TransmitPin.h"

#include <stdio.h>

ControlPackets createControlPackets() {
    Bit preambleBit = {
        1011,
        974
    };

    Bit longBit = {
        505,
        245
    };

    Bit shortBit = {
        255,
        490
    };

    Packet onPacket = {
        preambleBit,
        4,
        longBit,
        shortBit,
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0 }
    };

    Packet offPacket = {
            preambleBit,
            4,
            longBit,
            shortBit,
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };
    
    ControlPackets cp = {
        2,
        onPacket,
        offPacket,
        260
    };

    return cp;
}

BoilerControl::BoilerControl(TransmitPin *transmitPin) {
    this->transmitPin = transmitPin;
    this->controlPackets = createControlPackets();
}

BoilerControl::~BoilerControl() {
	delete this->transmitPin;
}

void BoilerControl::sendOnSignal() {
    printf("send ON signal\n");
    this->sendPackets(controlPackets.onPacket, controlPackets.nPacketRepeats, controlPackets.postPacketDelay);
}

void BoilerControl::sendOffSignal() {
    printf("send OFF signal\n");
    this->sendPackets(controlPackets.offPacket, controlPackets.nPacketRepeats, controlPackets.postPacketDelay);
}

void BoilerControl::sendPackets(Packet packet, const unsigned int nRepeats, const unsigned int postPacketDelayMillis) {
    for(int i = 0; i < nRepeats; i++) {
        this->sendPacket(packet);
        this->sendPostPacketDelay(postPacketDelayMillis);
    }

    this->sendPostPacketDelay(300);

    for(int i = 0; i < nRepeats; i++) {
        this->sendPacket(packet);
        this->sendPostPacketDelay(postPacketDelayMillis);
    }
}

void BoilerControl::sendPacket(Packet packet) {

    this->sendPacketPreamble(packet.preambleBit, packet.nPreambleBits);

    for(int i = 0; i < sizeof(packet.dataBits)/sizeof(packet.dataBits[0]); i++) {
        if(packet.dataBits[i] == 0) {
            this->sendBit(packet.offBit);
        } else {
            this->sendBit(packet.onBit);
        }
    }
}

void BoilerControl::sendPacketPreamble(Bit preambleBit, const unsigned int nPreambleBits) {
    for(int i = 0; i < nPreambleBits; i++) {
        this->sendBit(preambleBit);
    }
}

void BoilerControl::sendBit(Bit bit) {
    this->transmitPin->pullPinHighForPeriodSync(bit.highLengthMicros);
    this->transmitPin->pullPinLowForPeriodSync(bit.lowLengthMicros);
}

void BoilerControl::sendPostPacketDelay(const unsigned postPacketDelayMillis) {
    this->transmitPin->pullPinLowForPeriodSync(postPacketDelayMillis);
}
