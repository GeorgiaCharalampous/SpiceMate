#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <linux/i2c-dev.h>
#include <gpiod.h>

#ifndef Vibro_reg
#include <Vibro_reg.h>
#endif
#ifndef NDEBUG
#define DEBUG
#endif

static const char could_not_open_i2c2[] = "Could not open I2C.\n";

// default i2c address
#define DEFAULT_VIBRO_ADDRESS 0x5a

// default GPIO pin for EN pin
#define DEFAULT_EN_PIN 26

struct VIBRO4_settings{
    int default_i2c_bus = 1;
    uint8_t address = DEFAULT_VIBRO_ADDRESS;
    int EN_chip = 0;
    int EN_gpio = DEFAULT_EN_PIN;

    // Mode setup
    uint8_t standby                 = STANDBY;
    uint8_t rdy_internalTrig        = MODE_INT_TRIGGER;
    uint8_t rdy_externalTrig_edge   = MODE_EXT_TRIGGER_EDGE;
    uint8_t rdy_realTIME            = MODE_RTPLAYBACK;
    //uint8_t init_autocal_mode       = MODE_AUTO_CALIBRATION; // idle with internal trigger
    uint8_t init_diagnostic_mode    = MODE_DIAGNOSTIC; // idle with internal trigger


    // Auto-calibration register config section
    uint8_t init_autocal_mode       = MODE_AUTO_CALIBRATION; // idle with internal trigger
    uint8_t init_feedBack_reg       = (ERM_MODE|FB_BRAKE_FACTOR_3x|LOOP_GAIN_HIGH|BEMF_GAIN_LRA_20x);
    uint8_t init_ratedVoltage_reg   = RATED_VOLTAGE_ERM; //currently based on motor datasheet values
    uint8_t init_odClamp_reg        = OD_CLAMP_ERM; //currently based on motor datasheet values
    uint8_t init_control4_reg       = AUTO_CAL_TIME_150um; //AUTO_CAL_TIME_150um
    uint8_t init_control1_reg       = (STARTUP_BOOST|DRIVE_TIME); //default needs to change? //STARTUP_BOOST
    uint8_t init_control2_reg       = (BRAKE_STABILISER|INPUT_MODE_BIDIR|SAMPLE_TIME_300um|BLANKING_TIME|IDISS_TIME); //BRAKE_STABILISER
    uint8_t init_control3_reg       = (NG_THRESH_4pcnt|ERM_OPEN_LOOP|SUPPLY_COMP_DIS|DATA_FORMAT_RTP_SNG|LRA_DRIVE_MODE_1|INPUT_MODE_PWM|LRA_OPEN_LOOP);
    uint8_t init_go                 = VIBRO_GO;

    uint8_t vibro_library = LIBRARY_SELECT_LRA;
};

class VIBRO4_rpi{

    public:

    /**
     * Destructor 
    **/
    ~VIBRO4_rpi() {stop();}

    /**
     * Executes autocallibration procedure
    **/
    void autoCal();

    /**
     * Diagnosis
    **/
    void vibroDiagnostic();

    /**
     * Itialises vibration motor
    **/
    void initVibro(VIBRO4_settings vibro4settings = VIBRO4_settings());

    /**
     * stop the motor
    **/
    void stop();

    /**
     * Play haptic sequence in real time
    **/
    void playHaptic_realTime();

    /**
     * Play haptic sequence in real time
    **/
    void stopHaptic();
    
    /**
     * Amplitude setter
    **/

    void setAmplitude(uint8_t value){vAmplitude = value;};


    private:
    /**
     * Struct with settings for the vibro motor
    **/
    VIBRO4_settings motorSettings;

    /**
     * Current state of the mother
     * 1 when initated, 0 otherwise 
    **/
    int running = 0;

    /**
     * One byte writing method
     * \param reg the address of the register to write to
     * \param data the data to be written 
    **/
    void i2c_writeByte(uint8_t reg, unsigned data);

    /**
     * One byte reading method
     * \param reg the address of the register to read from
     * \param data the data to be written 
    **/
    unsigned i2c_readByte(uint8_t reg);

    /**
     * Pointer to the enable chip
    **/

    struct gpiod_chip *chipEN = nullptr;
    /**
     * Pointer to the enable pin
     **/
    struct gpiod_line *pinEN = nullptr;

    /**
     * Vibration amplitude. Default is 0
     * Needs to be assigned via setAmplitude()
    **/
    uint8_t vAmplitude = 0;

    /**
     * I2C file descriptor 
    **/
    int fd_i2c = -1;
};