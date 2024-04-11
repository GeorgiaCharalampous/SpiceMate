#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#ifndef DPcallbackChild
#include <DPcallbackChild.h>
#endif

#ifndef NDEBUG
#define DEBUG
#endif



/**
 * Processes input from the VL6180_x proximity sensor 
**/
class DataProcess {
    public:
    /**
     * Incoming reading 
    **/
    uint8_t value;

    /**
     * Flag that data has been received
    **/
    bool dataReceived = false;

    /**
     * Starts data processing on a separate thread 
    **/
    void start();
    /**
     * Stops data processing and joins the thread
    **/
    void stop();

    void registerCallback(DPcallbackInterface* cb);
    
    private:
    /**
     * Performs data thresholding and determines 
     * the action to be performed
    **/
    void thresholding();

    /**
     * Worker for the thread. Calls thresholding() 
    **/
    void worker();

    /**
     * Counts how many consequtive readings are
     * within dispensing range. Stays 0 when 
     * dispensing is active
    **/
	uint8_t counterAbove = 0;

    /**
     * Counts how many consequtive readings are
     * outside the dispensing range. Stays 0 when 
     * dispensing is inactive
    **/
    uint8_t counterBelow= 0;

    /**
     * Provides the upper limit of the dispensing
     * range (maximum distance away from the sensor) 
    **/
	uint8_t upperLimit = 180;

     /**
     * Provides the lower limit of the dispensing
     * range (maximum distance away from the sensor) 
    **/
	uint8_t lowerLimit = 20;

    /**
     * Processing thread 
    **/
    std::thread prosThread;

    /**
     * Flag that data processing is active/inactive 
    **/
    bool running = false;

    /**
     * Current operation status (dispensing active/inactive)
    **/
    bool isDispensing = false;

    /**
     *  Gives the state of the previous data reading.
     *  True when in the dispensing range, false otherwise
    **/
    bool lastValueInRange = false;

    /**
     *  Gives the state of the current data reading.
     *  True when in the dispensing range, false otherwise
    **/
    bool currentValueInRange = false;

    DPcallbackInterface* processCallback = nullptr;

};