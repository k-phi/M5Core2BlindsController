#ifndef __IBLINDS_H__
#define __IBLINDS_H__

class IBlinds {
   public:
    virtual ~IBlinds(){};
    virtual void open(unsigned int id) = 0;
    virtual void close(unsigned int id) = 0;
    virtual void stop(unsigned int id) = 0;
    virtual void tilt(unsigned int id) = 0;
};

#endif  // __IBLINDS_H__