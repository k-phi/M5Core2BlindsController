#ifndef __HTTPBLIND_H__
#define __HTTPBLIND_H__

#include "BlindConfiguration.h"
#include "IHttpClient.h"

class HttpBlind {
   public:
    HttpBlind(BlindConfiguration &blindConfiguration, IHttpClient *httpClient);
    ~HttpBlind() {};

   private:
    unsigned int Id_;
    char* iP_;
    bool canTilt_;
    float tiltPositionInPercent_;
    IHttpClient *httpClient_;
};

#endif // __HTTPBLIND_H__