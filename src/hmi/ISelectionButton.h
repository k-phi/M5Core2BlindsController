/*
  ISelectionButton.h

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

#ifndef __ISELECTIONBUTTON_H__
#define __ISELECTIONBUTTON_H__

class ISelectionButton {
   public:
    virtual ~ISelectionButton(){};
    virtual void load() = 0;
    virtual bool wasPressed() = 0;
    virtual void select() = 0;
    virtual void unselect() = 0;
    virtual bool isSelected() = 0;
    virtual unsigned int getId() = 0;
};

#endif  // __ISELECTIONBUTTON_H__