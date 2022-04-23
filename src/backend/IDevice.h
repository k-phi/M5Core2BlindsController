/*
  IDevice.h

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

#ifndef __IDEVICE_H__
#define __IDEVICE_H__

class IDevice {
   public:
    virtual ~IDevice(){};
    virtual void connectWiFi() = 0;
    virtual bool isWiFiConnected() = 0;
    virtual void powerOff() = 0;
    virtual float getBatteryLevelInPercent() = 0;
    virtual unsigned int getBatteryWarningLevel() = 0;
};

#endif  // __IDEVICE_H__