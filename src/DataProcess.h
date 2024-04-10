#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>

#ifndef NDEBUG
#define DEBUG
#endif

class DataProcess {
    public:
    uint8_t value;
    bool dataReceived = false;
    void start();
    void stop();
    
    private:
    void worker();
    void thresholding();
    
	uint8_t counter = 0;
	uint8_t upperLimit = 180;
	uint8_t lowerLimit = 20;
    std::thread prosThread;
    bool running = false;

};