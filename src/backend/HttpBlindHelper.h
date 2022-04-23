/*
  HttpBlindHelper.h

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

#ifndef __HTTPBLINDHELPER_H__
#define __HTTPBLINDHELPER_H__

class HttpBlindHelper {
   public:
    void getStateStringFromPayload(char* state, const char* payload);
    void getStateUrl(char* url, const char* iP);
    void getOpenUrl(char* url, const char* iP);
    void getCloseUrl(char* url, const char* iP);
    void getStopUrl(char* url, const char* iP);
    void getGoToUrl(char* url, const char* iP, float positionInPercent);
};

#endif  // __HTTPBLINDHELPER_H__