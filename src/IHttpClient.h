#ifndef __IHTTPCLIENT_H__
#define __IHTTPCLIENT_H__

class IHttpClient {
   public:
    virtual ~IHttpClient(){};
    virtual bool begin(const char* url) = 0;
    virtual int sendRequest(const char* type) = 0;
};

#endif  // __IHTTPCLIENT_H__