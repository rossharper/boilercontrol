#include <stdio.h>
#include <stdlib.h>
#include "boilercontrol.h"
#include "RaspberryPiTransmitPin.h"
#include "TransmitPinFactory.h"
#include "Constants.h"

int main(int argc, char *argv[]) {
    int PIN = 17;

    int callforheat = atoi(argv[1]);

    int realtimeOffset = nDefaultNonRealtimeOffset;
    if(const char* env_offset = getenv("CALLFORHEAT_OFFSET")) {
        realtimeOffset = atoi(env_offset);
    }
    if(argc > 2) {
        realtimeOffset = atoi(argv[2]);
    }
    printf("Realtime offset: %d\n", realtimeOffset);

    TransmitPin* transmitPin = TransmitPinFactory::create(PIN, realtimeOffset);
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
