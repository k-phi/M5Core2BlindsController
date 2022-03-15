#include "HttpBlind.h"

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
        // get state from shelly and setState()
    }
    return currentState_;
}

void HttpBlind::setState(HttpBlind::State state) {
    currentState_ = state;
    timeOfLastUpdate_ = std::chrono::system_clock::now();
}

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
