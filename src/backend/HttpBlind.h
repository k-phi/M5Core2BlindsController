/*
  HttpBlind.h

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

#ifndef __HTTPBLIND_H__
#define __HTTPBLIND_H__

#ifdef _M5Core2_H_
#undef min  // Avoid Arduino compiler issue with redefinition of min in chrono
#endif

#include <chrono>

#include "../BlindConfiguration.h"
#include "HttpBlindHelper.h"
#include "IBlind.h"
#include "IHttpClient.h"
#include "ILooper.h"

class HttpBlind : public IBlind, public ILooper {
   public:
    HttpBlind(BlindConfiguration &blindConfiguration, IHttpClient *httpClient,
              long &timoutInMilliseconds);
    virtual ~HttpBlind(){};
    virtual unsigned int getId();
    virtual void loop();
    virtual void open();
    virtual void close();
    virtual void stop();
    virtual void tilt();

   private:
    enum Command { NONE, OPEN, CLOSE, STOP, TILT };
    enum State { OPENING, CLOSING, STOPPED, UNKNOWN };
    State getState();
    void setState(State state);
    bool isTimeoutExceeded();
    void getRollerStateFromShelly(char *state);
    State convertToState(char *state);
    bool sendCommandToShelly(Command command);
    void loopOpen();
    void loopClose();
    void loopStop();
    void loopTilt();
    unsigned int id_;
    IHttpClient *httpClient_;
    long timeoutInMilliseconds_;
    bool canTilt_;
    char statusUrl_[200];
    char openUrl_[200];
    char closeUrl_[200];
    char stopUrl_[200];
    char goToPosUrl_[200];
    Command currentCommand_;
    State currentState_;
    bool isClosedBeforeTilt_;
    std::chrono::time_point<std::chrono::system_clock> timeOfLastUpdate_;
    HttpBlindHelper httpBlindHelper_;
};

#endif  // __HTTPBLIND_H__