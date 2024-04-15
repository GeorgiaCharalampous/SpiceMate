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

    //File descriptor for blocking the processing thread
    int* pfds_read = &fds[0];
    int* pfds_write = &fds[1];

    //File descriptor for blocking the actuating thread
    int* pfds_readM = &fdsM[0];
    int* pfds_writeM = &fdsM[1];

    VIBRO4_settings vmotor_Settings;
    VL6180x_rpi sensor_Instance;
    VIBRO4_rpi vibro_Instance;
    Servo_Driver servo_Instance(18);

    vibro_Instance.initVibro(vmotor_Settings);

    VL6180xcallbackChild passCallback;
    DPcallbackChild processingCallback;
    DataProcess printThreshold;
    Actuation actuator(&vibro_Instance,&servo_Instance);

    passCallback.setFileDescriptor(pfds_write);
    printThreshold.setFileDescriptor(pfds_read);
    processingCallback.setFileDescriptor(pfds_writeM);
    actuator.setFileDescriptor(pfds_readM);

    VL6180x_settings sensor_Settings;
    sensor_Instance.registerCallback(&passCallback);
    passCallback.registerDP(&printThreshold);
    printThreshold.registerCallback(&processingCallback);
    processingCallback.registerActuation(&actuator);

    sensor_Instance.startRangeContinuous(sensor_Settings);
    printThreshold.start();
    getchar();

    sensor_Instance.stop();
    close(*pfds_read);
    close(*pfds_write);
    printThreshold.stop();
    close(*pfds_readM);
    close(*pfds_writeM);
    actuator.~Actuation();

    sensor_Instance.unRegisterCallback();
    printThreshold.unRegisterCallback();

	return 0;
    
}