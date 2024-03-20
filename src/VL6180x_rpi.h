#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>
#include <assert.h>
//#include <VL6180xcallbackInterface.h>
#include <VL6180x_regAddress.h>
#include <VL6180X_regBitDefinitions.h>

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

// pointers to end-user configured settings
uint8_t* range_thresh_low = nullptr;
uint8_t* range_thresh_high = nullptr;
uint8_t* intermeasurement_period = nullptr;
uint8_t* max_convergence_time = nullptr;

struct VL6180x_settings{
    int default_i2c_bus = 1;
    uint8_t address = DEFAULT_VL6180X_ADDRESS;
    bool initPIGPIO = true;
    int int_gpio = DEFAULT_INT_TO_GPIO;

    /**
     * Initial sensor register settings 
    **/
    uint8_t system_mode_gpio1 = (ACTIVE_HIGH|GPIO_INTERRUPT_OUTPUT);

    uint8_t system_interrupt_config_gpio = RANGE_LEVEL_LOW;

    uint8_t system_interrupt_clear = RESET_INTERRUPT_CLEAR;

    uint8_t sysrange_thresh_low = *range_thresh_low;

    uint8_t sysrange_thresh_low = *range_thresh_high;

    uint8_t sysrange_intermeasurement_period = *intermeasurement_period;

    uint8_t sysrange_max_convergence_time = *max_convergence_time;

    uint8_t sysrange_range_check_enables = (SIGNAL_TO_NOISE_ENABLE);

    uint8_t sysrange_start = (RANGING_MODE_CONTINUOUS|RANGE_START_STOP_TRIGGER);
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
    void i2c_writeByte(uint8_t reg, unsigned data);
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