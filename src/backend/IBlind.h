/*
  IBlind.h

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

#ifndef __IBLIND_H__
#define __IBLIND_H__

class IBlind {
   public:
    virtual ~IBlind(){};
    virtual unsigned int getId() = 0;
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void stop() = 0;
    virtual void tilt() = 0;
};
#endif  // __IBLIND_H__