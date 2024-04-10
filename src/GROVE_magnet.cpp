#ifndef GROVE_magnet
#include "GROVE_magnet.h"
#endif

#include <bitset>
#include <fcntl.h>
#include <unistd.h>
//#include <sys/ioctl.h>

void GROVE_EMG::startMagnet(GROVE_settings settings){

    magnetSettings = settings;

    chipSIG = gpiod_chip_open_by_number(settings.SIG_chip);
    pinSIG = gpiod_chip_get_line(chipSIG,settings.SIG_gpio);

    gpiod_line_request_output(pinSIG,"Magnet",0); // open the pin to drive as output
    gpiod_line_set_value(pinSIG,1); // sets signal pin to high
}

void GROVE_EMG::stopMagnet(){
    gpiod_line_set_value(pinSIG,0); // set pin to low to turn off the magnet
}

void GROVE_EMG::stop(){
    gpiod_line_release(pinSIG);
    gpiod_chip_close(chipSIG);
}