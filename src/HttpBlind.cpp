#include "HttpBlind.h"

#include <cstring>

HttpBlind::HttpBlind(BlindConfiguration &blindConfiguration,
                     IHttpClient *httpClient, long &timeoutInMilliseconds)
    : Id_(blindConfiguration.Id),
      iP_(blindConfiguration.iP),
      canTilt_(blindConfiguration.canTilt),
      tiltPositionInPercent_(blindConfiguration.tiltPositionInPercent),
      httpClient_(httpClient),
      timeoutInMilliseconds_(timeoutInMilliseconds) {
    currentCommand_ = HttpBlind::Command::NONE;
    setState(HttpBlind::State::STOPPED);

    strcpy(statusUrl_, "http://");
    strcat(statusUrl_, iP_);
    strcat(statusUrl_, "/roller/0");
}

HttpBlind::~HttpBlind() { delete httpClient_; }

void HttpBlind::loop() {
    // switch case here for blind commands
}

void HttpBlind::open() { currentCommand_ = HttpBlind::Command::OPEN; }

void HttpBlind::close() { currentCommand_ = HttpBlind::Command::CLOSE; }

void HttpBlind::stop() { currentCommand_ = HttpBlind::Command::STOP; }

void HttpBlind::tilt() { currentCommand_ = HttpBlind::Command::TILT; }

HttpBlind::State HttpBlind::getState() {
    if (isTimeoutExceeded()) {
        currentState_ = getRollerStateFromShelly();
    }
    return currentState_;
}

void HttpBlind::setState(HttpBlind::State state) {
    currentState_ = state;
    timeOfLastUpdate_ = std::chrono::system_clock::now();
}

// move me to helper for better testing
bool HttpBlind::isTimeoutExceeded() {
    long durationInMilliseconds =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - timeOfLastUpdate_)
            .count();

    bool isExceeded = false;
    if (durationInMilliseconds > timeoutInMilliseconds_) {
        isExceeded = true;
    }
    return isExceeded;
}

HttpBlind::State HttpBlind::getRollerStateFromShelly() {
    httpClient_->begin(statusUrl_);
    int httpCode = httpClient_->sendRequest("GET");
    HttpBlind::State state = HttpBlind::State::UNKNOWN;
    if (httpCode == 200) {
        const char *payload = httpClient_->getPayload();
        char stateString[40];
        httpBlindHelper_.getStateStringFromPayload(stateString, payload);
        // convert string to state in helper
    }
    httpClient_->end();
    return state;
}
