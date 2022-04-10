#ifndef __BLINDCONFIGURATION_H__
#define __BLINDCONFIGURATION_H__

struct BlindConfiguration {
    unsigned int id;
    unsigned int buttonPositionX;
    unsigned int buttonPositionY;
    unsigned int buttonWidth;
    unsigned int buttonHeight;
    const char* iP;
    bool canTilt;
    float tiltPositionInPercent;
};

#endif  // __BLINDCONFIGURATION_H__