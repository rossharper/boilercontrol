#include "boilercontrol.h"

static const unsigned int nLongPulseLength = 953;
static const unsigned int nShortPulseLength = 365;
static const unsigned int nPauseLength = 365;
static const unsigned int nTxDelayLength = 4530;
static const unsigned int nPreTxDelay = 27810;
static const unsigned int nPostTxDelay = nPreTxDelay;

static const int ON_PACKETS[][nBitsPerPacket] = {{1,0,0,0,0,1,0,0,0,1,0,1,1,1,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1}, {1,1,1,1,1,0,1,1,1,0,1,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0}};
static const int OFF_PACKETS[][nBitsPerPacket] = {{1,0,0,0,0,1,0,0,0,1,0,1,1,1,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0}, {1,1,1,1,1,0,1,1,1,0,1,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1}};
static const int DELAY[] = {27810, 18069, 17512, 4721, 22327, 18916, 25870, nPostTxDelay};

BoilerControl::BoilerControl(int nTransmitterPin) {
    this->nTransmitterPin = nTransmitterPin;
}

void BoilerControl::sendOnSignal() {
    this->enableTransmit();
    this->sendPackets(ON_PACKETS);
}

void BoilerControl::sendOffSignal() {
    this->enableTransmit();
    this->sendPackets(OFF_PACKETS);
}

void BoilerControl::sendPackets(const int packets[][nBitsPerPacket]) {
    int nPacket = 0;

    digitalWrite(this->nTransmitterPin, HIGH);
    delayMicroseconds(nPreTxDelay);
    
    for(int nRepeats = 0; nRepeats < 4; nRepeats++) {
        this->sendPacket(packets[0]);
        delayMicroseconds(DELAY[nPacket]);
        nPacket++;
        this->sendPacket(packets[1]);
        delayMicroseconds(DELAY[nPacket]);
        nPacket++;
    }    

    digitalWrite(this->nTransmitterPin, HIGH);
    delayMicroseconds(nPostTxDelay);
}

void BoilerControl::sendPacket(const int packet[]) {
    this->sendTxStart();

    for(int bit = 0; bit < nBitsPerPacket; bit++) {
        if(packet[bit] == 1) {
            this->send1();
        }
        else {
            this->send0();
        }
    }

    digitalWrite(this->nTransmitterPin, HIGH);
}

void BoilerControl::sendTxStart() {
    digitalWrite(this->nTransmitterPin, LOW);
    delayMicroseconds(nTxDelayLength);
}

void BoilerControl::enableTransmit() {
    pinMode(this->nTransmitterPin, OUTPUT);
}

void BoilerControl::send1() {
    this->sendPulse(nLongPulseLength);
}

void BoilerControl::send0() {
    this->sendPulse(nShortPulseLength);
}

void BoilerControl::sendPulse(const unsigned int nPulseLength) {
    digitalWrite(this->nTransmitterPin, HIGH);
    delayMicroseconds(nPulseLength);
    digitalWrite(this->nTransmitterPin, LOW);
    delayMicroseconds(nPauseLength);
}
