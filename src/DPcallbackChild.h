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

    /**
     * Setter to the writing file descriptor 
    **/
    void setFileDescriptor (int* a)
	{
		pfds_write = a;
	}

    private:

    /**
	 * Pointer to actuation class.
	 * For setting states and initiating action.
	**/
    Actuation* pactuator = nullptr;

    /**
     * pointer to writing file descriptor of a pipe 
    **/

    int* pfds_write = nullptr;
};