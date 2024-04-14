#ifndef stdint
#include <stdint.h>
#endif
#ifndef stdio
#include <stdio.h>
#endif
#ifndef string
#include <string>
#endif

#ifndef NDEBUG
#define DEBUG
#endif

class Servo_Driver {
    public:
    /**
     * constructor 
     * \param pin_num an unsigned integer of the PWM pin on the RPI
    **/
    Servo_Driver(uint8_t pin_num);

    /**
     * destructor 
    **/
    ~Servo_Driver();

    /**
     * set Pulse Width Modulation frequency for servo motor (Note: Must be set before angle!)
     * \param f_hz a float with the frequency in hz
    **/
    void setFrequency(float f_hz);

    /**
     * set rotation angle for servo motor (Min:0 degrees, Ma:180 degrees)
     * \param angle_deg a float with the angle in degrees
    **/
    void setAngle(float angle_deg);

    /**
     * send Pulse Width Modulation signal to PWM pin
    **/
    void startPWM();

    /**
     * stop sending Pulse Width Modulation signal to PWM pin
    **/
    void stopPWM();

    private:

    std::string pwm_path;
    uint8_t pin_num;
    float period_ns;
    float dutycycle_ns;

};