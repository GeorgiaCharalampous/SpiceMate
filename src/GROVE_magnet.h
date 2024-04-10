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
#define DEFAULT_SIG_PIN 25

struct GROVE_settings{
    int SIG_chip = 0;
    int SIG_gpio = DEFAULT_SIG_PIN;

    uint8_t ON  = 1;
    uint8_t OFF = 0;
};


class GROVE_EMG{
    public:

    /**
     * destructor 
    **/
    ~GROVE_EMG() {stop();}

    void initMagnet(GROVE_settings groveSettings = GROVE_settings());

    void startMagnet();

    void stopMagnet();

    void stop();

    private:
    GROVE_settings  magnetSettings;

    struct gpiod_chip *chipSIG = nullptr;
    struct gpiod_line *pinSIG = nullptr;
};