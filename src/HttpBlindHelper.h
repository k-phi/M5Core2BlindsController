#ifndef __HTTPBLINDHELPER_H__
#define __HTTPBLINDHELPER_H__

class HttpBlindHelper {
   public:
    void getStateStringFromPayload(char* state, const char* payload);
};

#endif  // __HTTPBLINDHELPER_H__