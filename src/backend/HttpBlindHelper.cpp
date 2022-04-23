/*
  HttpBlindHelper.cpp

  Copyright (c) 2022, Philipp Kraft.

  This file is part of M5Core2BlindsController. M5Core2BlindsController is free
  software: you can redistribute it and/or modify it under the terms of the GNU
  Lesser General Public License as published by the Free Software Foundation,
  either version 3 of the License, or (at your option) any later version.

  M5Core2BlindsController is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
  for more details.

  You should have received a copy of the GNU Lesser General Public License along
  with M5Core2BlindsController. If not, see <https://www.gnu.org/licenses/>.
*/

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
    strcat(url, "/roller/0?go=open");
}

void HttpBlindHelper::getCloseUrl(char* url, const char* iP)
{
    strcpy(url, "http://");
    strcat(url, iP);
    strcat(url, "/roller/0?go=close");
}

void HttpBlindHelper::getStopUrl(char* url, const char* iP)
{
    strcpy(url, "http://");
    strcat(url, iP);
    strcat(url, "/roller/0?go=stop");
}

void HttpBlindHelper::getGoToUrl(char* url, const char* iP, float positionInPercent)
{
    strcpy(url, "http://");
    strcat(url, iP);
    char postfix[50];
    sprintf(postfix, "/roller/0?go=to_pos&roller_pos=%.0f", positionInPercent);
    strcat(url, postfix);
}
