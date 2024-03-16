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