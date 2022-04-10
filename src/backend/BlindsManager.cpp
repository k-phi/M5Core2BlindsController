#include "BlindsManager.h"
BlindsManager::BlindsManager(unsigned int *blindIds, unsigned int numberOfIds,
                             IEnablable *enablable, IBlinds *blinds,
                             ILooper *looper)
    : numberOfIds_(numberOfIds),
      enablable_(enablable),
      blinds_(blinds),
      looper_(looper) {
    blindIds_ = new unsigned int[numberOfIds_];
    for (unsigned int idIndex = 0; idIndex < numberOfIds_; idIndex++) {
        blindIds_[idIndex] = *(blindIds + idIndex);
    }
}

BlindsManager::~BlindsManager() { delete blindIds_; }

void BlindsManager::open() {
    for (unsigned int idIndex = 0; idIndex < numberOfIds_; idIndex++) {
        unsigned int blindId = blindIds_[idIndex];
        if (enablable_->isEnabled(blindId)) {
            blinds_->open(blindId);
        }
    }
}

void BlindsManager::close() {
    for (unsigned int idIndex = 0; idIndex < numberOfIds_; idIndex++) {
        unsigned int blindId = blindIds_[idIndex];
        if (enablable_->isEnabled(blindId)) {
            blinds_->close(blindId);
        }
    }
}

void BlindsManager::stop() {
    for (unsigned int idIndex = 0; idIndex < numberOfIds_; idIndex++) {
        unsigned int blindId = blindIds_[idIndex];
        if (enablable_->isEnabled(blindId)) {
            blinds_->stop(blindId);
        }
    }
}

void BlindsManager::tilt() {
    for (unsigned int idIndex = 0; idIndex < numberOfIds_; idIndex++) {
        unsigned int blindId = blindIds_[idIndex];
        if (enablable_->isEnabled(blindId)) {
            blinds_->tilt(blindId);
        }
    }
}

void BlindsManager::enable(unsigned int id) { enablable_->enable(id); }

void BlindsManager::disable(unsigned int id) { enablable_->disable(id); }

bool BlindsManager::isEnabled(unsigned int id) {
    return enablable_->isEnabled(id);
}

void BlindsManager::loop() { looper_->loop(); }

unsigned int BlindsManager::getId() { return 0; }
