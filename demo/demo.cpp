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
    VL6180x_rpi sensor;
    VIBRO4_rpi vibro;
    Servo_Driver servo(18);

    vibro.initVibro(vmotor_Settings);

    VL6180xcallbackChild passCallback;
    DPcallbackChild processingCallback;
    DataProcess processor;
    Actuation actuator(&vibro,&servo);

    passCallback.setFileDescriptor(pfds_write);
    processor.setFileDescriptor(pfds_read);
    processingCallback.setFileDescriptor(pfds_writeM);
    actuator.setFileDescriptor(pfds_readM);

    VL6180x_settings sensor_Settings;
    sensor.registerCallback(&passCallback);
    passCallback.registerDP(&processor);
    processor.registerCallback(&processingCallback);
    processingCallback.registerActuation(&actuator);

    sensor.startRangeContinuous(sensor_Settings);
    processor.start();
    getchar();

    sensor.stop();
    close(*pfds_read);
    close(*pfds_write);
    processor.stop();
    close(*pfds_readM);
    close(*pfds_writeM);
    actuator.~Actuation();

    sensor.unRegisterCallback();
    processor.unRegisterCallback();

	return 0;
    
}