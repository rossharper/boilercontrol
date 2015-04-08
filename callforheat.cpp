#include <stdio.h>
#include <stdlib.h>
#include "boilercontrol.h"
#include "RaspberryPiTransmitPin.h"
#include "TransmitPinFactory.h"

int main(int argc, char *argv[]) {
    int PIN = 0;

    int callforheat = atoi(argv[1]);

    TransmitPin* transmitPin = TransmitPinFactory::create(PIN);
    if(!transmitPin) return 1;

    BoilerControl* boilerControl = new BoilerControl(transmitPin);

    if(callforheat == 1) {
        printf("send ON signal\n");
        boilerControl->sendOnSignal();
    }
    else {
        printf("send OFF signal\n");
        boilerControl->sendOffSignal();
    }

    delete boilerControl;

    return 0;
}
