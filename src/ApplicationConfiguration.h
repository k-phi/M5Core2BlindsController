#ifndef __APPLICATIONCONFIGURATION_H__
#define __APPLICATIONCONFIGURATION_H__

struct ApplicationConfiguration {
    char ssid[100];
    char passphrase[100];
    long idleTimeoutBeforeShutdownInMilliseconds;
    long timeoutBetweenHttpRequestsInMilliseconds;
};

#endif  // __APPLICATIONCONFIGURATION_H__