/*
  IDeviceData.h

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

#ifndef __IDEVICEDATA_H__
#define __IDEVICEDATA_H__

class IDeviceData {
   public:
    virtual ~IDeviceData(){};
    virtual void saveBool(const char* key, bool value) = 0;
    virtual bool loadBool(const char* key) = 0;
    virtual bool clear() = 0;
    virtual void close() = 0;
};

#endif  // __IDEVICEDATA_H__