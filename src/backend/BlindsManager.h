/*
  BlindsManager.h

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

#ifndef __BLINDSMANAGER_H__
#define __BLINDSMANAGER_H__

#include "IBlind.h"
#include "IBlinds.h"
#include "IDevice.h"
#include "IEnablable.h"
#include "ILooper.h"

class BlindsManager : public IBlind, public IEnablable, public ILooper {
   public:
    BlindsManager(unsigned int *blindIds, unsigned int numberOfIds,
                  IEnablable *enablable, IBlinds *blinds, ILooper *looper);
    ~BlindsManager();
    virtual void open();
    virtual void close();
    virtual void stop();
    virtual void tilt();
    virtual void enable(unsigned int id);
    virtual void disable(unsigned int id);
    virtual bool isEnabled(unsigned int id);
    virtual void loop();
    virtual unsigned int getId();

   private:
    unsigned int *blindIds_;
    unsigned int numberOfIds_;
    IEnablable *enablable_;
    IBlinds *blinds_;
    ILooper *looper_;
};

#endif  // __BLINDSMANAGER_H__