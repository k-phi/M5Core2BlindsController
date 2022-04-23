/*
  ITouchButton.h

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

#ifndef __ITOUCHBUTTON_H__
#define __ITOUCHBUTTON_H__

class ITouchButton {
   public:
    virtual ~ITouchButton(){};
    virtual void load() = 0;
    virtual bool wasPressed() = 0;
    virtual void setLabel(const char* label) = 0;
};

#endif  // __ITOUCHBUTTON_H__