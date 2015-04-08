#include "boilercontrol.h"

#include "TransmitPin.h"

static const unsigned int nLongPulseLength = 953;
static const unsigned int nShortPulseLength = 365;
static const unsigned int nPauseLength = 365;
static const unsigned int nTxDelayLength = 4530;
static const unsigned int nPreTxDelay = 27810;
static const unsigned int nPostTxDelay = nPreTxDelay;

static const int ON_PACKETS[][nBitsPerPacket] = {
    {1,0,0,0,0,1,0,0,0,1,0,1,1,1,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,0,1,1,1,0,1,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0}
};
static const int OFF_PACKETS[][nBitsPerPacket] = {
    {1,0,0,0,0,1,0,0,0,1,0,1,1,1,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,0,1,1,1,0,1,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1}
};
static const int DELAY[] = {27810, 18069, 17512, 4721, 22327, 18916, 25870, nPostTxDelay};

BoilerControl::BoilerControl(TransmitPin *transmitPin) {
    this->transmitPin = transmitPin;
}

BoilerControl::~BoilerControl() {
	delete this->transmitPin;
}

void BoilerControl::sendOnSignal() {
    this->sendPackets(ON_PACKETS);
}

void BoilerControl::sendOffSignal() {
    this->sendPackets(OFF_PACKETS);
}

void BoilerControl::sendPackets(const int packets[][nBitsPerPacket]) {
    int nPacket = 0;

    this->transmitPin->pullPinLowForPeriodSync(nPreTxDelay);
    
    for(int nRepeats = 0; nRepeats < 4; nRepeats++) {
        this->sendPacket(packets[0], DELAY[nPacket]);
        nPacket++;
        this->sendPacket(packets[1], DELAY[nPacket]);
        nPacket++;
    }    

    this->transmitPin->pullPinLowForPeriodSync(nPostTxDelay);
}

void BoilerControl::sendPacket(const int packet[], const unsigned int nPostPacketDelay) {
    this->sendTxStart();

    for(int bit = 0; bit < nBitsPerPacket; bit++) {
        if(packet[bit] == 1) {
            this->send1();
        }
        else {
            this->send0();
        }
    }

    this->transmitPin->pullPinLowForPeriodSync(nPostPacketDelay);
}

void BoilerControl::sendTxStart() {
    this->transmitPin->pullPinHighForPeriodSync(nTxDelayLength);
}

void BoilerControl::send1() {
    this->sendPulse(nLongPulseLength);
}

void BoilerControl::send0() {
    this->sendPulse(nShortPulseLength);
}

void BoilerControl::sendPulse(const unsigned int nPulseLength) {
	this->transmitPin->pullPinLowForPeriodSync(nPulseLength);
	this->transmitPin->pullPinHighForPeriodSync(nPauseLength);
}
