#include "GROVE_magnet.h"

int main(int argc, char *argv[]){

    GROVE_EMG magnetInstance;
    GROVE_settings Settings_Struct;

    printf("Hi");

    magnetInstance.initMagnet(Settings_Struct);

    sleep(1);

    magnetInstance.startMagnet();

    sleep(1);

    magnetInstance.stopMagnet();

    sleep(1);

    magnetInstance.startMagnet();

    sleep(1);

    magnetInstance.stop();
}