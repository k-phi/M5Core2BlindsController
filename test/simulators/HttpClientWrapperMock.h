#ifndef __HTTPCLIENTWRAPPERMOCK_H__
#define __HTTPCLIENTWRAPPERMOCK_H__

#include "../../src/IHttpClient.h"
#include "gmock/gmock.h"

class HttpClientWrapperMock : public IHttpClient {
   public:
    MOCK_METHOD(bool, begin, (const char* url), (override));
    MOCK_METHOD(int, sendRequest, (const char* type), (override));
    MOCK_METHOD(const char*, getPayload, (), (override));
    MOCK_METHOD(void, end, (), (override));
};

#endif  // __HTTPCLIENTWRAPPERMOCK_H__