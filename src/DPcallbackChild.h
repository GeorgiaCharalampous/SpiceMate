#ifndef  DPcallbackInterface
#include <DPcallbackInterface.h>
#endif
#ifndef VIBRO4_rpi
#include <VIBRO4_rpi.h>
#endif

class DPcallbackChild : public DPcallbackInterface{
    virtual void dataProcessed(bool status);
    VIBRO4_rpi* vmotor = NULL;

    public:
    void registerMotor(VIBRO4_rpi* motor){
        vmotor = motor;
    }

};