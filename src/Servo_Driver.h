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
     * Constructor 
     * \param pin_num an unsigned integer of the PWM pin on the RPI
    **/
    Servo_Driver(uint8_t pin_num);

    /**
     * Destructor 
    **/
    ~Servo_Driver();

    /**
     * Set Pulse Width Modulation frequency for servo motor (Note: Must be set before angle!)
     * \param f_hz a float with the frequency in hz
    **/
    void setFrequency(float f_hz);

    /**
     * Set rotation angle for servo motor (Min:0 degrees, Ma:180 degrees)
     * \param angle_deg a float with the angle in degrees
    **/
    void setAngle(float angle_deg);

    /**
     * Send Pulse Width Modulation signal to PWM pin
    **/
    void startPWM();

    /**
     * Stop sending Pulse Width Modulation signal to PWM pin
    **/
    void stopPWM();

    private:

    /**
     * Path to sysf pwm class object
    **/
    std::string pwm_path;
    /**
     * Pin number 
    **/
    uint8_t pin_num;

    /**
     * PWM period in nanoseconds 
    **/
    float period_ns;

    /**
     * PWM active time in nanoseconds
    **/
    float dutycycle_ns;

};