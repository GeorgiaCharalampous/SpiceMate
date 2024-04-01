#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>
#include <assert.h>
#include <thread>
#include <Vibro_reg.h>

#ifndef NDEBUG
#define DEBUG
#endif

// default i2c address
#define DEFAULT_VIBRO_ADDRESS   

struct VIBRO4_settings{
    
};

class VIBRO_rpi{

};