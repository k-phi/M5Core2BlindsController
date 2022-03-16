#ifndef __HTTPCLIENTWRAPPER_H__
#define __HTTPCLIENTWRAPPER_H__

#include <HTTPClient.h>

#include "IHttpClient.h"

class HttpClientWrapper : public IHttpClient {
   public:
    HttpClientWrapper();
    ~HttpClientWrapper(){};
    virtual bool begin(const char* url);
    virtual int sendRequest(const char* type);
    virtual const char* getPayload();
    virtual void end();

   private:
    HTTPClient httpClient_;
};

#endif  // __HTTPCLIENTWRAPPER_H__