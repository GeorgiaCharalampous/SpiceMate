#ifndef  DPcallback
#include <DPcallback.h>
#endif
#ifndef Actuation
#include <Actuation.h>
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
    void registerActuation(Actuation* Actuator){
        pactuator = Actuator;
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
    Actuation* pactuator = NULL;

    int* pfds_write;
};