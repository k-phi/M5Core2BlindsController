#include "HttpClientWrapper.h"

HttpClientWrapper::HttpClientWrapper() { httpClient_.setReuse(true); }

bool HttpClientWrapper::begin(const char* url) {
    String urlString = String(url);
    bool isSuccessful = httpClient_.begin(urlString);
    return isSuccessful;
}

int HttpClientWrapper::sendRequest(const char* type) {
    int httpCode = httpClient_.sendRequest(type);
    return httpCode;
}

const char* HttpClientWrapper::getPayload() {
    String payLoad = httpClient_.getString();
    return getPayload.c_str();
}

void HttpClientWrapper::end() { httpClient_.end(); }
