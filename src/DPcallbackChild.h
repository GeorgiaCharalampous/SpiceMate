#ifndef  DPcallback
#include <DPcallback.h>
#endif
#ifndef VIBRO4_rpi
#include <VIBRO4_rpi.h>
#endif

class DPcallbackChild : public DPcallback{

    /**
     * Callback for when data has been processed 
    **/
    virtual void dataProcessed(bool status);


    public:
    /**
	 * Registers the pointer to the output device (motor)
	**/
    void registerMotor(VIBRO4_rpi* motor){
        vmotor = motor;
    }

    void setFileDescriptor (int* a)
	{
		pfds_write = a;
	}

    private:

    /**
	 * Pointer to output device.
	 * For setting states.
	**/
    VIBRO4_rpi* vmotor = NULL;

    int* pfds_write;
};