#ifndef __IBLINDCOMMANDSCONTRACT_H__
#define __IBLINDCOMMANDSCONTRACT_H__

class IBlindCommandsontract {
   public:
    virtual ~IBlindCommandsontract(){};
    virtual void open(unsigned int id) = 0;
    virtual void close(unsigned int id) = 0;
    virtual void stop(unsigned int id) = 0;
    virtual void tilt(unsigned int id) = 0;
    virtual void loop() = 0;
};

#endif  // __IBLINDCOMMANDSCONTRACT_H__