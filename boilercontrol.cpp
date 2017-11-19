#include "boilercontrol.h"

#include "TransmitPin.h"

#include <stdio.h>

//static const unsigned int nLongPulseLength = 953;
//static const unsigned int nShortPulseLength = 365;
//static const unsigned int nPauseLength = 365;
//static const unsigned int nTxDelayLength = 4530;
//static const unsigned int nPreTxDelay = 27810;
//static const unsigned int nPostTxDelay = nPreTxDelay;
//
//static const int ON_PACKETS[][nBitsPerPacket] = {
//    {1,0,0,0,0,1,0,0,0,1,0,1,1,1,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
//    {1,1,1,1,1,0,1,1,1,0,1,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0}
//};
//static const int OFF_PACKETS[][nBitsPerPacket] = {
//    {1,0,0,0,0,1,0,0,0,1,0,1,1,1,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
//    {1,1,1,1,1,0,1,1,1,0,1,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1}
//};
//static const int DELAY[] = {27810, 18069, 17512, 4721, 22327, 18916, 25870, nPostTxDelay};



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

//    this->sendTxStart();
//
//    for(int bit = 0; bit < nBitsPerPacket; bit++) {
//        if(packet[bit] == 1) {
//            this->send1();
//        }
//        else {
//            this->send0();
//        }
//    }
//
//    this->transmitPin->pullPinLowForPeriodSync(nPostPacketDelay);
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

//void BoilerControl::sendTxStart() {
//    this->transmitPin->pullPinHighForPeriodSync(nTxDelayLength);
//}
//
//void BoilerControl::send1() {
//    this->sendPulse(nLongPulseLength);
//}
//
//void BoilerControl::send0() {
//    this->sendPulse(nShortPulseLength);
//}
//
//void BoilerControl::sendPulse(const unsigned int nPulseLength) {
//	this->transmitPin->pullPinLowForPeriodSync(nPulseLength);
//	this->transmitPin->pullPinHighForPeriodSync(nPauseLength);
//}
