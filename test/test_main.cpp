#ifndef Vibro4_rpi
#include "Vibro4_rpi.h"
#endif

int main(int argc, char *argv[]){
    
    VIBRO4_rpi motor_Instance;
    VIBRO4_settings Settings_Struct;

    uint8_t hapticAmp = 255;

    motor_Instance.initVibro(Settings_Struct);
    printf("Driver initialised \n");
    //motor_Instance.vibroDiagnostic();
    //sleep(1);
    motor_Instance.playHaptic_realTime(hapticAmp);
    //motor_Instance.playHaptic_preDef();
    printf("Motor started \n");
    
    char a = getchar();
    if(a == '1')
    {
        motor_Instance.stopHaptic();
        printf("Haptic stopped\n");
        sleep(1);
        //motor_Instance.stop();
    }
    // else if (a == '2')
    // {
    //     motor_Instance.stopHaptic();
    //     sleep(1);
    //     motor_Instance.stop();
    // }

    return 0;    
}