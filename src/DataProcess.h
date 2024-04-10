#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


class DataProcess
{
    public:
    uint8_t value;
    bool dataReceived = false;
    
    private:
    void thresholding();
    
	uint8_t counter = 0;
	uint8_t upperLimit = 180;
	uint8_t lowerLimit = 20;

};