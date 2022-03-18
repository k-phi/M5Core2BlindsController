#ifndef __HTTPBLINDHELPER_H__
#define __HTTPBLINDHELPER_H__

class HttpBlindHelper {
   public:
    void getStateStringFromPayload(char* state, const char* payload);
    void getStateUrl(char* url, const char* iP);
    void getOpenUrl(char* url, const char* iP);
    void getCloseUrl(char* url, const char* iP);
    void getStopUrl(char* url, const char* iP);
    void getGoToUrl(char* url, const char* iP, float positionInPercent);
};

#endif  // __HTTPBLINDHELPER_H__