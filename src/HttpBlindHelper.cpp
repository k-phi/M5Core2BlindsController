#include "HttpBlindHelper.h"

#include <cstring>
#include <stdio.h>

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

void HttpBlindHelper::getStateUrl(char* url, const char* iP)
{
    strcpy(url, "http://");
    strcat(url, iP);
    strcat(url, "/roller/0");
}

void HttpBlindHelper::getOpenUrl(char* url, const char* iP)
{
    strcpy(url, "http://");
    strcat(url, iP);
    strcat(url, "/roller/0/go=open");
}

void HttpBlindHelper::getCloseUrl(char* url, const char* iP)
{
    strcpy(url, "http://");
    strcat(url, iP);
    strcat(url, "/roller/0/go=close");
}

void HttpBlindHelper::getStopUrl(char* url, const char* iP)
{
    strcpy(url, "http://");
    strcat(url, iP);
    strcat(url, "/roller/0/go=stop");
}

void HttpBlindHelper::getGoToUrl(char* url, const char* iP, float positionInPercent)
{
    strcpy(url, "http://");
    strcat(url, iP);
    char postfix[50];
    sprintf(postfix, "/roller/0/go=to_pos,roller_pos=%.0f", positionInPercent);
    strcat(url, postfix);
}
