#include "HttpBlind.h"
HttpBlind::HttpBlind(BlindConfiguration &blindConfiguration,
                     IHttpClient *httpClient)
    : Id_(blindConfiguration.Id),
      iP_(blindConfiguration.iP),
      canTilt_(blindConfiguration.canTilt),
      tiltPositionInPercent_(blindConfiguration.tiltPositionInPercent),
      httpClient_(httpClient) {
          
      }
