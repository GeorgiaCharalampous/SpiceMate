/*
 * Demo program for spice dispenser utilising classes for a proximity sensor (VL6180X), ERM vibrational 
 * motor driven by the DRV2605/L and an SG90 Micro Servo.
 * During operation, dispensing is triggered when an object is introduced to the region monitored by the sensor. Motor activation
 * deactivation occurs in response to retained presence of the object within the sensor field.
 *
 * Copyright (c) 2007  MontaVista Software, Inc.
 * Copyright (c) 2007  Anton Vorontsov <avorontsov@ru.mvista.com>
 * Copyright (c) 2013-2022  Bernd Porr <mail@berndporr.me.uk>
 * Copyright (c) 2024 Viktoriya Kaleva, Hasitha Senevirathne, Georgia Charalampous <spicemate_auto@outlook.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License.
 *
 */

#ifndef VL6180x_rpi
#include "VL6180x_rpi.h"
#endif


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
   
    passCallback.setFileDescriptor(pfds_write);
    processor.setFileDescriptor(pfds_read);
    processingCallback.setFileDescriptor(pfds_writeM);

    Actuation actuator(&vibro,&servo);
    actuator.setFileDescriptor(pfds_readM);

    VL6180x_settings sensor_Settings;
    sensor.registerCallback(&passCallback);
    passCallback.registerDP(&processor);
    processor.registerCallback(&processingCallback);
    processingCallback.registerActuation(&actuator);

    actuator.start();
    processor.start();
    sensor.startRangeContinuous(sensor_Settings);
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