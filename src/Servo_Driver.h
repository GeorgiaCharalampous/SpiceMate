#ifndef stdint
#include <stdint.h>
#endif
#ifndef stdio
#include <stdio.h>
#endif
#ifndef string
#include <string.h>
#endif

#ifndef NDEBUG
#define DEBUG
#endif

class Servo_Driver {
    public:
    /**
     * constructor 
    **/
    Servo_Driver(uint8_t pin_num) {};

    /**
     * destructor 
    **/
    ~Servo_Driver() {};

    /**
     * set Pulse Width Modulation frequency for servo motor (Note: Must be set before angle!)
    **/
    void setFrequency(uint_8 f_hz);

    /**
     * set rotation angle for servo motor (Min:0 degrees, Ma:180 degrees)
    **/
    void setAngle(uint_8 angle_deg);

    /**
     * send Pulse Width Modulation signal to PWM pin
    **/
    void startPWM();

    /**
     * stop sending Pulse Width Modulation signal to PWM pin
    **/
    void stopPWM();

    private:

    string pwm_path;
    uint8_t pin_num;
    int period_ns;
    int dutycycle_ns;

};