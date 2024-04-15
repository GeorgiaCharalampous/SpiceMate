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
     * \param Actuator a pointer to an instance of
     * the class Actuation
	**/
    void registerActuation(Actuation* Actuator){
        pactuator = Actuator;
    }

    /**
     * Sets a file descriptor to write to
     * To signal to other threads that data has
     * been processed
     * \param a a pointer to an existing file descriptor
    **/
    void setFileDescriptor (int* a)
	{
		pfds_write = a;
	}

    private:

    /**
	 * Pointer to actuation class.
	 * For setting states and initiating action.
     * Initially a nullptr. Must be set using
     * registerActuation()
	**/
    Actuation* pactuator = nullptr;

    /**
     * Pointer to the file descriptor to write to.
     * Used to signal to other threads.
     * Initially a nullptr. Must be set using
     * setFileDescriptor()
    **/
    int* pfds_write = nullptr;
};