/*
  BlindsManager.cpp

  Copyright (c) 2022, Philipp Kraft.

  This file is part of M5Core2BlindsController. M5Core2BlindsController is free
  software: you can redistribute it and/or modify it under the terms of the GNU
  Lesser General Public License as published by the Free Software Foundation,
  either version 3 of the License, or (at your option) any later version.

  M5Core2BlindsController is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
  for more details.

  You should have received a copy of the GNU Lesser General Public License along
  with M5Core2BlindsController. If not, see <https://www.gnu.org/licenses/>.
*/

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
