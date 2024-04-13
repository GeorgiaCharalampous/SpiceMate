#ifndef Servo_Driver
#include "Servo_Driver.h"
#endif
// Only used for sleep
#ifndef
#include<unistd.h>  
#endif

int main(int argc, char *argv[]){
    
    uint8_t Servo_pin = 18;

    Servo_Driver Servo_Instance(Servo_pin);

    Servo_Instance.setFrequency(50);

    Servo_Instance.setAngle(0);

    Servo_Instance.startPWM();

    sleep(2);

    Servo_Instance.setAngle(180);

    sleep(2);

    Servo_Instance.setAngle(135);

    sleep(2);

    Servo_Instance.setAngle(90);

    sleep(2);

    Servo_Instance.setAngle(45);

    sleep(2);

    Servo_Instance.setAngle(0);

    sleep(2);

    Servo_Instance.stopPWM();

	return 0;
    
}