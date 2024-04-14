#ifndef VL6180x_rpi
#include "VL6180x_rpi.h"
#endif
// #ifndef VIBRO4_rpi
// #include "VIBRO4_rpi.h"
// #endif



int main(int argc, char *argv[]){
    int fds[2],fdsM[2];
    pipe(fds);
    pipe(fdsM);

    int* pfds_read = &fds[1];
    int* pfds_write = &fds[2];

    //File descriptor for communication between
    //the processing and motor classes
    int* pfds_readM = &fdsM[1];
    int* pfds_writeM = &fdsM[2];


    VL6180x_rpi sensor_Instance;
    VIBRO4_rpi motor_Instance;
    VL6180xcallbackChild passCallback;
    DPcallbackChild processingCallback;
    DataProcess printThreshold;

    passCallback.setFileDescriptor(pfds_write);
    printThreshold.setFileDescriptor(pfds_read);
    processingCallback.setFileDescriptor(pfds_writeM);
    motor_Instance.setFileDescriptor(pfds_readM);

    int Range_Intermeasurement_period = 100; //ms
    int Range_Max_convergence_time = 15; //ms

    VL6180x_settings sensor_Settings;
    VIBRO4_settings motor_Settings;
    printf("Range threshold low is %u . \n",sensor_Settings.sysrange_thresh_low);
    sensor_Instance.registerCallback(&passCallback);
    passCallback.registerDP(&printThreshold);
    printThreshold.registerCallback(&processingCallback);
    processingCallback.registerMotor(&motor_Instance);

    motor_Instance.initVibro(motor_Settings);
    sleep(3);
    motor_Instance.setAmplitude(255);

    sensor_Instance.startRangeContinuous(sensor_Settings);
    printThreshold.start();
    motor_Instance.start();
    // printf("Motor initialised \n");
    // printf("Acquisisition started \n");
    getchar();
	sensor_Instance.stop();
    printThreshold.stop();
    motor_Instance.stop();   

    sensor_Instance.unRegisterCallback();
    printThreshold.unRegisterCallback();
	return 0;
    
}