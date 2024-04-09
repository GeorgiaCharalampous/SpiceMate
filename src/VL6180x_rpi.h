#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//#include <pigpio.h>
#include <linux/i2c-dev.h>
#include <gpiod.h>

#include <assert.h>
#include <thread>
#ifndef  VL6180xcallbackChild
#include <VL6180xcallbackChild.h>
#endif
#include <VL6180x_regAddress.h>
#include <VL6180X_regBitDefinitions.h>

#ifndef NDEBUG
#define DEBUG
#endif

static const char could_not_open_i2c[] = "Could not open I2C.\n";

// default i2c address 
#define DEFAULT_VL6180X_ADDRESS 0x29

// default GPIO pins for the interrupt and sensor enable
#define DEFAULT_INT_TO_GPIO 17
#define DEFAULT_EN_TO_GPIO 4

// default interrupt timeout
#define ISR_TIMEOUT 1000

// pointers to end-user configured settings
//extern uint8_t* ptr_range_thresh_low;
//uint8_t* ptr_range_thresh_high = nullptr;
//uint8_t* ptr_intermeasurement_period = nullptr;
//uint8_t* ptr_max_convergence_time = nullptr;

struct VL6180x_settings{
    int default_i2c_bus = 1;
    uint8_t sensor_address = DEFAULT_VL6180X_ADDRESS;
    //bool initPIGPIO = true;
    int int_chip = 0;
    int int_gpio = DEFAULT_INT_TO_GPIO;
    int en_chip = 0;
    int en_gpio = DEFAULT_EN_TO_GPIO;

    /**
     * Initial sensor register settings 
    **/
    uint8_t system_mode_gpio1 = (ACTIVE_LOW|GPIO_INTERRUPT_OUTPUT);

    uint8_t system_interrupt_config_gpio = RANGE_NEW_SAMPLE_READY;

    uint8_t system_interrupt_clear = (CLEAR_RANGE_INT|CLEAR_ALS_INT|CLEAR_ERROR_INT);

    //uint8_t sysrange_thresh_low = *ptr_range_thresh_low;
    uint8_t sysrange_thresh_low = 0x00;

    //uint8_t sysrange_thresh_high = *ptr_range_thresh_high;
    uint8_t sysrange_thresh_high = 0xFF;

    //uint8_t sysrange_intermeasurement_period = *ptr_intermeasurement_period;
    uint8_t sysrange_intermeasurement_period = 0xFF;

    //uint8_t sysrange_max_convergence_time = *ptr_max_convergence_time;
    uint8_t sysrange_max_convergence_time = 63;

    uint8_t sysrange_range_check_enables = (SIGNAL_TO_NOISE_ENABLE);

    uint8_t sysrange_start = (RANGING_MODE_CONTINUOUS|RANGE_START_STOP_TRIGGER);
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
    void startRangeContinuous(VL6180x_settings vl6180xsettings = VL6180x_settings());

    /**
     * stop data acquisition 
    **/
    void stop();

    /**
     * Registers the callback on sample arrival.
     * \param cb Pointer to the callback interface. 
    **/
    void registerCallback(VL6180xcallback* cb);
    
    /**
     * Unregisters the callback
    **/
    void unRegisterCallback();

    void getStatus();
    private:
    VL6180x_settings sensorSettings;
    VL6180xcallback* sensorCallback = nullptr;
    std::thread proxThread;//Proximity sensor thread
    int running = 0;
    void i2c_writeTwoBytes(uint8_t reg, unsigned data);
    void i2c_writeByte(uint8_t reg, unsigned data);
    unsigned i2c_readTwoBytes(uint8_t reg);
    unsigned i2c_readByte(uint8_t reg);
    int i2c_readConversion();

    const uint8_t reg_congig = 1;
    const uint8_t reg_lo_thres = 2;
    const uint8_t reg_hi_thres = 3;

    void dataReady();
    //void run();
    void worker();
    /*static void gpioISR(int,int,uint32_t,void* userdata){
        ((VL6180x_rpi*)userdata)->dataReady();
    }*/
    struct gpiod_chip *chipINT = nullptr;
    struct gpiod_line *pinINT = nullptr;
    struct gpiod_chip *chipEN = nullptr;
    struct gpiod_line *pinEN = nullptr;

    int fd_i2c = -1;
};