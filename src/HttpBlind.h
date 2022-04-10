#ifndef __HTTPBLIND_H__
#define __HTTPBLIND_H__

#ifdef _M5Core2_H_
#undef min  // Avoid Arduino compiler issue with redefinition of min in chrono
#endif

#include <chrono>

#include "BlindConfiguration.h"
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