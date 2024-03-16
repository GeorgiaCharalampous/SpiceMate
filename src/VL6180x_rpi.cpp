#include "VL6180x_rpi.h"

void VL6180x_rpi::start(VL6180xsettings settings){
    sensorSettings = settings;

    //Initialise pigpio
    if(settings.initPIGPIO){
        int cfg = gpioCfgGetInternals();
        cfg |= PI_CFG_NOSIGHANDLER;
        gpioCfgSetInternals(cfg);
        int r = gpioInitialise();
        if (r < 0) {
            char msg[] = "Cannot init pigpio.";
            #ifdef DEBUG
            fprintf (stderr, "%s\n",msg);
            #endif
            throw msg;
        }
    }
}_