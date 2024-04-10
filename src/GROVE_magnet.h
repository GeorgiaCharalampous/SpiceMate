#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <thread>
//#include <linux/i2c-dev.h>
#include <gpiod.h>

#ifndef NDEBUG
#define DEBUG
#endif

//static const char could_not_open_i2c[] = "Could not open I2C.\n";

// default i2c address
//#define DEFAULT_VIBRO_ADDRESS 0x5a

// default GPIO pin for EN pin
#define DEFAULT_EN_PIN 25

struct GROVE_settings{
    int EN_chip = 0;
    int EN_gpio = DEFAULT_EN_PIN;

    uint8_t ON  = 1;
    uint8_t OFF = 0;
};


class GROVE_EMG{
    public:

    /**
     * destructor 
    **/
    ~GROVE_EMG() {stopMagnet();}

    void startMagnet();

    void stopMagnet();

    private:
    GROVE_settings  magnetSettings;

    struct gpiod_chip *chipEN = nullptr;
    struct gpiod_line *pinEN = nullptr;
}