#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>
#include <assert.h>
//#include <VL6180xcallbackInterface.h>
#include <VL6180x_regAddress.h>
#include <VL6180X_regOptions.h>

#ifndef NDEBUG
#define DEBUG
#endif

static const char could_not_open_i2c[] = "Could not open I2C.\n";

// default i2c address 
#define DEFAULT_VL6180X_ADDRESS 0x29

// default GPIO pin for the interrupt
#define DEFAULT_INT_TO_GPIO 17

// default interrupt timeout
#define ISR_TIMEOUT 1000


struct VL6180x_settings{
    int i2c_bus = 1;

    uint8_t address = DEFAULT_VL6180X_ADDRESS;

    bool initPIGPIO = true;

    int int_gpio = DEFAULT_INT_TO_GPIO;
};

class VL6180x_rpi {
    public:
    /**
     * destructor 
    **/
    ~VL6180x_rpi() {stop();}

    virtual void hasSample(uint8_t sample) = 0;

    /**
     * start data acquisition 
    **/
    void start (VL6180x_settings vl6180xsettings = VL6180x_settings());

    /**
     * stop data acquisition 
    **/
    void stop();

    // /**
    //  * Registers the callback on sample arrival.
    //  * \param cb Pointer to the callback interface. 
    // **/
    // void registerCallback(VL6180xcallback* cb);
    
    // /**
    //  * Unregisters the callback
    // **/
    // void unRegisterCallback();

    private:
    VL6180x_settings sensorSettings;
    /*
    VL6180xcallback* sensorCallback = nullptr;
    */
    void i2c_writeWord(uint8_t reg, unsigned data);
    unsigned i2c_readWord(uint8_t reg);
    int i2c_readConversion();

    const uint8_t reg_congig = 1;
    const uint8_t reg_lo_thres = 2;
    const uint8_t reg_hi_thres = 3;

    void dataReady();
    static void gpioISR(int,int,uint32_t,void* userdata){
        ((VL6180x_rpi*)userdata)->dataReady();
    }

};