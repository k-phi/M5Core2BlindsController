#include "HttpBlindHelper.h"

#include <cstring>

const char* HttpBlindHelper::getStateStringFromPayload(const char* payload) {
    const char* colon;
    colon = strchr(payload, ':');
    const char* comma;
    comma = strchr(payload, ',');
    char stateString[40];
    int stateWordLenght = comma - colon - 3;
    strncpy(stateString, (colon + 2), stateWordLenght);
    stateString[stateWordLenght] = '\0';
    return (const char*) stateString;
}
