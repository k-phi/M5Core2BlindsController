#ifndef __HTTPCLIENTWRAPPER_H__
#define __HTTPCLIENTWRAPPER_H__

#include <HTTPClient.h>

#include "../backend/IHttpClient.h"

class HttpClientWrapper : public IHttpClient {
   public:
    HttpClientWrapper();
    ~HttpClientWrapper(){};
    virtual bool begin(const char* url);
    virtual int sendRequest(const char* type);
    virtual void getPayload(char* payload);
    virtual void end();

   private:
    HTTPClient httpClient_;
};

#endif  // __HTTPCLIENTWRAPPER_H__