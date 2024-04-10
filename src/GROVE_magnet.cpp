#ifndef GROVE_magnet
#include "GROVE_magnet.h"
#endif

#include <bitset>
#include <fcntl.h>
#include <unistd.h>
//#include <sys/ioctl.h>

void GROVE_EMG::initMagnet(GROVE_settings settings){

    printf("Initiate magnet");
    magnetSettings = settings;

    chipSIG = gpiod_chip_open_by_number(settings.SIG_chip);
    pinSIG = gpiod_chip_get_line(chipSIG,settings.SIG_gpio);

    printf("Chip and line open");

    gpiod_line_request_output(pinSIG,"Magnet",0); // open the pin to drive as output
    gpiod_line_set_value(pinSIG,settings.OFF); // sets signal pin to high

    printf("Value set to off in init");

}

void GROVE_EMG::startMagnet(){
    gpiod_line_set_value(pinSIG,magnetSettings.ON);
    printf("Magnet on");

}

void GROVE_EMG::stopMagnet(){
    gpiod_line_set_value(pinSIG,magnetSettings.OFF); // set pin to low to turn off the magnet
    printf("Magnet off");

}

void GROVE_EMG::stop(){
    gpiod_line_set_value(pinSIG,magnetSettings.OFF); // set pin to low to turn off the magnet
    gpiod_line_release(pinSIG);
    gpiod_chip_close(chipSIG);
    printf("Exit");

}