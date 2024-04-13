#ifndef Servo_Driver
#include "Servo_Driver.h"
#endif

Servo_Driver::Servo_Driver(uint8_t pin_num){
    
    Servo_Driver::pin_num = pin_num;

    if (pin_num == 12 || pin_num == 18){
        FILE* fd = fopen("/sys/class/pwm/pwmchip0/export","w");
        fprintf(fd,"0");
        fclose(fd);
        pwm_path = "/sys/class/pwm/pwmchip0/pwm0";
    }
    else if (pin_num == 13 || pin_num == 19){
        FILE* fd = fopen("/sys/class/pwm/pwmchip0/export","w");
        fprintf(fd,"1");
        fclose(fd);
        pwm_path = "/sys/class/pwm/pwmchip0/pwm1";
    }
    else {
        fprintf(stderr,"%u is not a valid PWM pin.\n",pin_num);
        throw "Invalid PWM pin";
    }
    printf("Servo driver initialised at PWM pin %u.\n",pin_num);
};

Servo_Driver::~Servo_Driver(){

    if (pin_num == 12 || pin_num == 18){
        FILE* fd = fopen("/sys/class/pwm/pwmchip0/unexport","w");
        fprintf(fd,"0");
        fclose(fd);
    }
    else if (pin_num == 13 || pin_num == 19){
        FILE* fd = fopen("/sys/class/pwm/pwmchip0/unexport","w");
        fprintf(fd,"1");
        fclose(fd);
    }
    printf("Servo driver closed at PWM pin %u.\n",pin_num);
};


void Servo_Driver::setFrequency(float f_hz){
    period_ns = (1/f_hz)*(1000000000);
    std::string path = pwm_path + "/period";
    FILE* fd = fopen(path.c_str(),"w");
    fprintf(fd,"%u",(int)period_ns);
    fclose(fd);
    printf("Servo frequency set to %u Hz at pin %u.\n",(int)f_hz,pin_num);
};


void Servo_Driver::setAngle(float angle_deg){
    dutycycle_ns = ((angle_deg/180)*(period_ns/10))+500000;
    std::string path = pwm_path + "/duty_cycle";
    FILE* fd = fopen(path.c_str(),"w");
    fprintf(fd,"%u",(int)dutycycle_ns);
    fclose(fd);
    printf("Servo angle set to %u degrees at pin %u.\n",(int)angle_deg,pin_num);
};


void Servo_Driver::startPWM(){
    std::string path = pwm_path + "/enable";
    FILE* fd = fopen(path.c_str(),"w");
    fprintf(fd,"1");
    fclose(fd);
    printf("Servo activated at pin %u.\n",pin_num);
}


void Servo_Driver::stopPWM() {
    std::string path = pwm_path + "/enable";
    FILE* fd = fopen(path.c_str(),"w");
    fprintf(fd,"0");
    fclose(fd);
    printf("Servo deactivated at pin %u.\n",pin_num);
}
