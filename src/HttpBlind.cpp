#include "HttpBlind.h"

#include <cstring>

HttpBlind::HttpBlind(BlindConfiguration &blindConfiguration,
                     IHttpClient *httpClient, long &timeoutInMilliseconds)
    : canTilt_(blindConfiguration.canTilt),
      httpClient_(httpClient),
      timeoutInMilliseconds_(timeoutInMilliseconds) {
    httpBlindHelper_.getStateUrl(statusUrl_, blindConfiguration.iP);
    httpBlindHelper_.getOpenUrl(openUrl_, blindConfiguration.iP);
    httpBlindHelper_.getCloseUrl(closeUrl_, blindConfiguration.iP);
    httpBlindHelper_.getStopUrl(stopUrl_, blindConfiguration.iP);
    httpBlindHelper_.getGoToUrl(goToPosUrl_, blindConfiguration.iP,
                                blindConfiguration.tiltPositionInPercent);
    currentCommand_ = HttpBlind::Command::NONE;
    setState(HttpBlind::State::STOPPED);
}

HttpBlind::~HttpBlind() { delete httpClient_; }

void HttpBlind::loop() {
    switch (currentCommand_) {
        case HttpBlind::Command::OPEN: {
            if (sendCommandToShelly(HttpBlind::Command::OPEN)) {
                setState(HttpBlind::State::OPENING);
                currentCommand_ = HttpBlind::Command::NONE;
            }
            break;
        }
        case HttpBlind::Command::CLOSE: {
            if (sendCommandToShelly(HttpBlind::Command::CLOSE)) {
                setState(HttpBlind::State::CLOSING);
                currentCommand_ = HttpBlind::Command::NONE;
            }
            break;
        }
        case HttpBlind::Command::STOP: {
            if (sendCommandToShelly(HttpBlind::Command::STOP)) {
                setState(HttpBlind::State::STOPPED);
                currentCommand_ = HttpBlind::Command::NONE;
            }
            break;
        }
        case HttpBlind::Command::TILT: {
            if (!canTilt_) {
                currentCommand_ = HttpBlind::Command::NONE;
            } else if (!isClosedBeforeTilt_) {
                if (sendCommandToShelly(HttpBlind::Command::CLOSE)) {
                    setState(HttpBlind::State::CLOSING);
                    isClosedBeforeTilt_ = true;
                }
            } else if (isClosedBeforeTilt_ &&
                       getState() == HttpBlind::State::STOPPED) {
                if (sendCommandToShelly(HttpBlind::Command::TILT)) {
                    setState(HttpBlind::State::OPENING);
                    isClosedBeforeTilt_ = false;
                    currentCommand_ = HttpBlind::Command::NONE;
                }
            }
            break;
        }
        default:
            break;
    }
}

void HttpBlind::open() { currentCommand_ = HttpBlind::Command::OPEN; }

void HttpBlind::close() { currentCommand_ = HttpBlind::Command::CLOSE; }

void HttpBlind::stop() { currentCommand_ = HttpBlind::Command::STOP; }

void HttpBlind::tilt() { currentCommand_ = HttpBlind::Command::TILT; }

HttpBlind::State HttpBlind::getState() {
    if (isTimeoutExceeded()) {
        char stateString[50];
        getRollerStateFromShelly(stateString);
        currentState_ = convertToState(stateString);
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

void HttpBlind::getRollerStateFromShelly(char *state) {
    httpClient_->begin(statusUrl_);
    int httpCode = httpClient_->sendRequest("GET");
    if (httpCode == 200) {
        char payload[400];
        httpClient_->getPayload(payload);
        char stateString[40];
        httpBlindHelper_.getStateStringFromPayload(state, payload);
    } else {
        strcpy(state, "unknown");
    }
    httpClient_->end();
}

HttpBlind::State HttpBlind::convertToState(char *state) {
    HttpBlind::State stateEnum = HttpBlind::State::UNKNOWN;
    if (strcmp("open", state) == 0) {
        stateEnum = HttpBlind::State::OPENING;
    } else if (strcmp("close", state) == 0) {
        stateEnum = HttpBlind::State::CLOSING;
    } else if (strcmp("stop", state) == 0) {
        stateEnum = HttpBlind::State::STOPPED;
    }
    return stateEnum;
}

bool HttpBlind::sendCommandToShelly(HttpBlind::Command command) {
    bool isSuccessful = true;
    switch (command) {
        case HttpBlind::Command::OPEN:
            httpClient_->begin(openUrl_);
            break;
        case HttpBlind::Command::CLOSE:
            httpClient_->begin(closeUrl_);
            break;
        case HttpBlind::Command::STOP:
            httpClient_->begin(stopUrl_);
            break;
        case HttpBlind::Command::TILT:
            httpClient_->begin(goToPosUrl_);
            break;
        default:
            return isSuccessful;
    }

    int httpCode = httpClient_->sendRequest("GET");
    if (httpCode != 200) {
        isSuccessful = false;
    }
    httpClient_->end();

    return isSuccessful;
}
