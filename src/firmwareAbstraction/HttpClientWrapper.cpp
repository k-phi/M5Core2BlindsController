#include "HttpClientWrapper.h"

#include <cstring>

HttpClientWrapper::HttpClientWrapper() {
    Serial.println("Creating HTTP client...");
    httpClient_.setReuse(true);
    Serial.println("HTTP client created.");
}

bool HttpClientWrapper::begin(const char* url) {
    String urlString = String(url);
    bool isSuccessful = httpClient_.begin(urlString);
    return isSuccessful;
}

int HttpClientWrapper::sendRequest(const char* type) {
    int httpCode = httpClient_.sendRequest(type);
    return httpCode;
}

void HttpClientWrapper::getPayload(char* payload) {
    String payLoad = httpClient_.getString();
    strcpy(payload, payLoad.c_str());
}

void HttpClientWrapper::end() { httpClient_.end(); }
