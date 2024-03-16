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

class VL6180x_rpi {

};