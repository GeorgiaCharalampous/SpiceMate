#ifndef Servo_Driver
#include "Servo_Driver.h"
#endif

Servo_Driver::Servo_Driver(uint8_t pin_num){
    
    Servo_Driver.pin_num = pin_num

    if (pin_num == (12||18)){
        FILE* fd = fopen("/sys/class/pwm/pwmchip0/export","w");
        fprintf(fd,0);
        fclose(fd);
        Servo_Driver.pwm_path = "/sys/class/pwm/pwmchip0/pwm0"
    else if (pin_num == (13||19)){
        FILE* fd = fopen("/sys/class/pwm/pwmchip0/export"),"w";
        fprintf(fd,1);
        fclose(fd);
        Servo_Driver.pwm_path = "/sys/class/pwm/pwmchip0/pwm1"
    }
    else fprintf(stderr,"%u is not a valid PWM pin.\n",pin_num);
    }
    printf("Servo driver initialised for PWM pin %u.\n",pin_num);
};


Servo_Driver::~Servo_Driver(){

    if (Servo_Driver.pin_num == (12||18)){
        FILE* fd = fopen("/sys/class/pwm/pwmchip0/unexport","w");
        fprintf(fd,0);
        fclose(fd);
    else if (Servo_Driver.pin_num == (13||19)){
        FILE* fd = fopen("/sys/class/pwm/pwmchip0/unexport"),"w";
        fprintf(fd,1);
        fclose(fd);
    }
    }
    printf("Servo driver closed for PWM pin %u.\n",Servo_Driver.pin_num);
};


void Servo_Driver::setFrequency(uint8_t f_hz){
    Servo_Driver.period_ns = (1/f_hz)*pow(10,9);
    FILE* fd = fopen(Servo_Driver.pwm_path+"/period","w");
    fprintf(fd,Servo_Driver.period_ns);
    fclose(fd);
    printf("Servo frequency set to %u Hz at pin %u.\n",f_hz,Servo_Driver.pin_num);
};


void Servo_Driver::setAngle(uint8_t angle_deg){
    Servo_Driver.dutycycle_ns = ((angle_deg/180)*(Servo_Driver.period_ns/10)+500000);
    FILE* fd = fopen(Servo_Driver.pwm_path+"/duty_cycle","w");
    fprintf(fd,Servo_Driver.dutycycle_ns);
    fclose(fd);
    printf("Servo angle set to %u degrees at pin %u.\n",angle_deg,Servo_Driver.pin_num);
};


void Servo_Driver::startPWM(){
    FILE* fd = fopen(Servo_Driver.pwm_path+"/enable","w");
    fprintf(pwm_path,1);
    fclose(fd);
    printf("Servo activated at pin %u.\n",Servo_Driver.pin_num);
}


void Servo_Driver::stopPWM() {
    FILE* fd = fopen(Servo_Driver.pwm_path+"/enable","w");
    fprintf(pwm_path,0);
    fclose(fd);
    printf("Servo deactivated at pin %u.\n",Servo_Driver.pin_num);
}
