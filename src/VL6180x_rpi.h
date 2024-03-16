#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>
#include <assert.h>

#ifndef NDEBUG
#define DEBUG
#endif

static const char could_not_open_i2c[] = "Could not open I2C.\n";

// default i2c address 
#define DEFAULT_VL6180X_ADDRESS 0x29

// default GPIO pin for the interrupt
#define DEAFULAT_INT_TO_GPIO 17

struct VL6180Xsettings{
    int i2c_bus = 1;

    uint8_t address = DEFAULT_VL6180X_ADDRESS;

    bool initPIGPIO = true;
};

class VL6180x_rpi {
    public:
    /**
     * destructor 
    **/
    ~VL6180x_rpi() {stop();}

    /**
     * start data acquisition 
    **/
   void start (VL6180Xsettings vl6180xsettings = VL6180Xsettings());

    /**
     * stop data acquisition 
    **/
    void stop();

    private:
    VL6180Xsettings sensorSettings;

};