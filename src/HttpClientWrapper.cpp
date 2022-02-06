#include "HttpClientWrapper.h"

bool HttpClientWrapper::begin(const char* url) {
    String urlString = String(url);
    bool isSuccessful = httpClient_.begin(urlString);
    return isSuccessful;
}

int HttpClientWrapper::sendRequest(const char* type) {
    int httpCode = httpClient_.sendRequest(type);
    return httpCode;
}
