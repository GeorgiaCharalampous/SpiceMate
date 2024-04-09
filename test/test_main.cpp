#ifndef Vibro4_rpi
#include "Vibro4_rpi.h"
#endif

int main(int argc, char *argv[]){
    
    VIBRO4_rpi motor_Instance;
    VIBRO4_settings Settings_Struct;

    uint8_t hapticAmp = 128;

    motor_Instance.initVibro(Settings_Struct);
    printf("Driver initialised \n");
    motor_Instance.playHaptic_realTime(hapticAmp);
    printf("Motor started \n");
    getchar();
    motor_Instance.stopHaptic();
    getchar();
    motor_Instance.stop();
    return 0;    


}