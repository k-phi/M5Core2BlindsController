#include "HttpBlindHelper.h"

#include <cstring>

void HttpBlindHelper::getStateStringFromPayload(char* state, const char* payload) {
    const char* colon;
    colon = strchr(payload, ':');
    const char* comma;
    comma = strchr(payload, ',');
    char stateString[40];
    int stateWordLenght = comma - colon - 3;
    strncpy(stateString, (colon + 2), stateWordLenght);
    stateString[stateWordLenght] = '\0';
    strcpy(state, stateString);
}
