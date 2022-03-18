#ifndef __HTTPBLIND_H__
#define __HTTPBLIND_H__

#include <chrono>

#include "BlindConfiguration.h"
#include "HttpBlindHelper.h"
#include "IHttpClient.h"

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
    void getRollerStateFromShelly(char *state);
    State convertToState(char *state);
    bool sendCommandToShelly(Command command);
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