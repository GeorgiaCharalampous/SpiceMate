#ifndef Vibro4_rpi
#include "Vibro4_rpi.h"
#endif

int main(int argc, char *argv[]){
    
    VIBRO4_rpi motor_Instance;
    VIBRO4_settings Settings_Struct;

    uint8_t hapticAmp = 255;

    motor_Instance.initVibro(Settings_Struct);
    printf("Driver initialised \n");
    // for (int i = 0; i < 100; i++)
    // {
    //     printf("... \n");
    // };

    //sleep(5);
    motor_Instance.playHaptic_realTime(hapticAmp);
    printf("Motor started \n");
    
    getchar();
    motor_Instance.stopHaptic();
    printf("Haptic stopped\n");
    sleep(1);
    motor_Instance.stop();
    return 0;    
}