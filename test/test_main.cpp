#ifndef VL6180x_rpi
#include "VL6180x_rpi.h"
#endif
#ifndef VIBRO4_rpi
#include "VIBRO4_rpi.h"
#endif

// #ifndef VL6180xcallbackChild
// #include "VL6180xcallbackChild.h"
// #endif



int main(int argc, char *argv[]){
    
    VL6180x_rpi sensor_Instance;
    VL6180xcallbackChild passCallback;
    DataProcess printThreshold;
    VIBRO4_rpi motor_Instance;


    int Range_Intermeasurement_period = 100; //ms
    int Range_Max_convergence_time = 15; //ms

    VL6180x_settings sensor_Settings;
    VIBRO4_settings motor_Settings;
    printf("Range threshold low is %u . \n",sensor_Settings.sysrange_thresh_low);
    /*
    Sensor_Instance.registerCallback(&printCallback);
    Sensor_Instance.startRangeContinuous(Settings_Struct);
    for(int i = 0; i < 1000000; i++){
        Sensor_Instance.getStatus();
    }
    printf("Done \n");
    Sensor_Instance.stop();
    printf("Test finished \n");
    return 0;
    */
    sensor_Instance.registerCallback(&passCallback);
    passCallback.registerDP(&printThreshold);
    sensor_Instance.startRangeContinuous(sensor_Settings);
    printf("Acquisisition started \n");
    printThreshold.start();
    getchar();
	sensor_Instance.stop();
    printThreshold.stop();
	return 0;
    
}
/*
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
    
    getchar();
    
    motor_Instance.stopHaptic();

    getchar();
    
    motor_Instance.stop();

    return 0;    
    */