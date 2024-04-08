#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <thread>
#include <linux/i2c-dev.h>
#include <gpiod.h>
#include <Vibro_reg.h>

#ifndef NDEBUG
#define DEBUG
#endif

static const char could_not_open_i2c[] = "Could not open I2C.\n";

// default i2c address
#define DEFAULT_VIBRO_ADDRESS

// default GPIO pin for EN pin
#define DEFAULT_EN_PIN 25

struct VIBRO4_settings{
    int default_i2c_bus = 1;
    uint8_t address = DEFAULT_VIBRO_ADDRESS;
    int drdy_chip = 0;
    int int_gpio = DEFAULT_EN_PIN;

    // init setup
    uint8_t init_autocal_mode = MODE_AUTO_CALIBRATION; // idle with internal trigger

    // Auto-calibration register config section
    uint8_t init_feedBack_reg = (LRA_MODE|FB_BRAKE_FACTOR_3x|LOOP_GAIN_HIGH);
    uint8_t init_ratedVoltage_reg = RATED_VOLTAGE_DEFAULT; //default needs to change?
    uint8_t init_odClamp_reg = OD_CLAMP; //default needs to change?
    uint8_t init_control4_reg = AUTO_CAL_TIME_500um;
    uint8_t init_control1_reg = DRIVE_TIME; //default needs to change?
    uint8_t init_control2_reg = SAMPLE_TIME_300um|BLANKING_TIME|IDISS_TIME;
    uint8_t init_go = VIBRO_GO;

    uint8_t vibro_library = LIBRARY_SELECT_LRA;
    
    //put on standby after autocal
    uint8_t standby = STANDBY;
    uint8_t device_rdy = DEVICE_RDY;
};

class VIBRO4_rpi{

    public:
    /**
     * Itialises vibration motor
    **/
    bool initVibro(VIBRO4_settings vibro4settings = VIBRO4_settings());

    /**
     * Play haptic sequence
    */
    void playHaptic();

    private:
    VIBRO4_settings motorSettings;
    //std::thread proxThread;//Proximity sensor thread
    //int running = 0;
    //void i2c_writeTwoBytes(uint8_t reg, unsigned data);
    void i2c_writeByte(uint8_t reg, unsigned data);
    //unsigned i2c_readTwoBytes(uint8_t reg);
    unsigned i2c_readByte(uint8_t reg);
    int i2c_readConversion();

    struct gpiod_chip *chipDRDY = nullptr;
    struct gpiod_line *pinDRDY = nullptr;
};