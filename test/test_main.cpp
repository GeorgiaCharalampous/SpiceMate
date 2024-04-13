#ifndef Vibro4_rpi
#include "Vibro4_rpi.h"
#endif

int main(int argc, char *argv[]){
    
    VIBRO4_rpi motor_Instance;
    VIBRO4_settings Settings_Struct;

    motor_Instance.initVibro(Settings_Struct);
    printf("Driver initialised \n");

    motor_Instance.playHaptic_realTime(25);
    sleep(5);
    motor_Instance.playHaptic_realTime(50);
    sleep(5);
    motor_Instance.playHaptic_realTime(100);
    sleep(5);
    motor_Instance.playHaptic_realTime(150);
    sleep(5);
    
    getchar();
    motor_Instance.stopHaptic();
    printf("Haptic stopped\n");
    motor_Instance.stop();
    return 0;    
}