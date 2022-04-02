#include "BlindsAccess.h"
BlindsAccess::BlindsAccess(IBlind **blinds, ILooper **loopers,
                           unsigned int numberOfBlinds)
    : numberOfBlinds_(numberOfBlinds) {
    blinds_ = new IBlind *[numberOfBlinds];
    loopers_ = new ILooper *[numberOfBlinds];
    for (unsigned int blindIndex = 0; blindIndex < numberOfBlinds_;
         blindIndex++) {
        *(blinds_ + blindIndex) = blinds[blindIndex];
        *(loopers_ + blindIndex) = loopers[blindIndex];
    }
}

BlindsAccess::~BlindsAccess() {
    for (unsigned int blindIndex = 0; blindIndex < numberOfBlinds_;
         blindIndex++) {
        // TODO: Figure out while the BlindsAccessTest fail when deleting the
        // pointers delete *(blinds_ + blindIndex); delete *(loopers_ +
        // blindIndex);
    }
}

void BlindsAccess::open(unsigned int id) {
    for (unsigned int blindIndex = 0; blindIndex < numberOfBlinds_;
         blindIndex++) {
        IBlind *blind = *(blinds_ + blindIndex);
        if (blind && (id == blind->getId())) {
            blind->open();
        }
    }
}

void BlindsAccess::close(unsigned int id) {
    for (unsigned int blindIndex = 0; blindIndex < numberOfBlinds_;
         blindIndex++) {
        IBlind *blind = *(blinds_ + blindIndex);
        if (blind && (id == blind->getId())) {
            blind->close();
        }
    }
}

void BlindsAccess::stop(unsigned int id) {
    for (unsigned int blindIndex = 0; blindIndex < numberOfBlinds_;
         blindIndex++) {
        IBlind *blind = *(blinds_ + blindIndex);
        if (blind && (id == blind->getId())) {
            blind->stop();
        }
    }
}

void BlindsAccess::tilt(unsigned int id) {
    for (unsigned int blindIndex = 0; blindIndex < numberOfBlinds_;
         blindIndex++) {
        IBlind *blind = *(blinds_ + blindIndex);
        if (blind && (id == blind->getId())) {
            blind->tilt();
        }
    }
}

void BlindsAccess::loop() {
    for (unsigned int looperIndex = 0; looperIndex < numberOfBlinds_;
         looperIndex++) {
        ILooper *looper = *(loopers_ + looperIndex);
        if (looper) {
            looper->loop();
        }
    }
}
