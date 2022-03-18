#ifndef __HTTPBLIND_H__
#define __HTTPBLIND_H__

#include <chrono>

#include "BlindConfiguration.h"
#include "IHttpClient.h"
#include "HttpBlindHelper.h"

class HttpBlind {
   public:
    HttpBlind(BlindConfiguration &blindConfiguration, IHttpClient *httpClient,
              long &timoutInMilliseconds);
    ~HttpBlind();
    void loop();
    void open();
    void close();
    void stop();
    void tilt();

   private:
    enum Command { NONE, OPEN, CLOSE, STOP, TILT };
    enum State { OPENING, CLOSING, STOPPED, UNKNOWN };
    State getState();
    void setState(State state);
    bool isTimeoutExceeded();
    State getRollerStateFromShelly();
    unsigned int Id_;
    const char *iP_;
    bool canTilt_;
    float tiltPositionInPercent_;
    IHttpClient *httpClient_;
    Command currentCommand_;
    State currentState_;
    long timeoutInMilliseconds_;
    std::chrono::time_point<std::chrono::system_clock> timeOfLastUpdate_;
    char statusUrl_[200];
    HttpBlindHelper httpBlindHelper_;
};

#endif  // __HTTPBLIND_H__