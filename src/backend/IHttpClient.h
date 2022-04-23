/*
  IHttpClient.h

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

#ifndef __IHTTPCLIENT_H__
#define __IHTTPCLIENT_H__

class IHttpClient {
   public:
    virtual ~IHttpClient(){};
    virtual bool begin(const char* url) = 0;
    virtual int sendRequest(const char* type) = 0;
    virtual void getPayload(char* payload) = 0;
    virtual void end() = 0;
};

#endif  // __IHTTPCLIENT_H__