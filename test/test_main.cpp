#ifndef VL6180x_rpi
#include "VL6180x_rpi.h"
#endif
// #ifndef VIBRO4_rpi
// #include "VIBRO4_rpi.h"
// #endif



int main(int argc, char *argv[]){
    
    VL6180x_rpi sensor_Instance;
    VIBRO4_rpi motor_Instance;
    VL6180xcallbackChild passCallback;
    DPcallbackChild processingCallback;
    DataProcess printThreshold;

    int Range_Intermeasurement_period = 100; //ms
    int Range_Max_convergence_time = 15; //ms

    VL6180x_settings sensor_Settings;
    VIBRO4_settings motor_Settings;
    printf("Range threshold low is %u . \n",sensor_Settings.sysrange_thresh_low);
    sensor_Instance.registerCallback(&passCallback);
    passCallback.registerDP(&printThreshold);
    printThreshold.registerCallback(&processingCallback);
    processingCallback.registerMotor(&motor_Instance);


    sensor_Instance.startRangeContinuous(sensor_Settings);
    printThreshold.start();
    motor_Instance.initVibro(motor_Settings);
    motor_Instance.setAmplitude(255);
    motor_Instance.start();
    printf("Motor initialised \n");
    printf("Acquisisition started \n");
    getchar();
    motor_Instance.~VIBRO4_rpi();
    printThreshold.stop();
	sensor_Instance.stop();

    sensor_Instance.unRegisterCallback();
    printThreshold.unRegisterCallback();
	return 0;
    
}