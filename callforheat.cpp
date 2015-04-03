#include <stdio.h>
#include <stdlib.h>
#include "boilercontrol.h"

int main(int argc, char *argv[]) {
    int PIN = 0;

    int callforheat = atoi(argv[1]);

    if(wiringPiSetup() == -1) return 1;

    BoilerControl* boilerControl = new BoilerControl(PIN);

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
