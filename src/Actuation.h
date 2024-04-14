#ifndef VIBRO4_rpi
#include<VIBRO4_rpi.h>
#endif
#ifndef Servo_Driver
#include<Servo_Driver.h>
#endif
#include <thread>


/**
 * the actuating class of the dispenser
 * makes use of a vibrational and servo motors
**/
class Actuation{
    public:
    /**
     * Constructor
     * \param  vMotor a pointer to a vibrational motor
     * \param sMotor a pointer to a servo motor
    **/
   Actuation(VIBRO4_rpi* VibroMotor,Servo_Driver* ServoMotor,int* FD);

   /**
    * 
    **/ 

   void stop();

    /**
    * Current status of the motor. 
    **/
   bool activate = false;

   private:
   VIBRO4_rpi* pvMotor;
   Servo_Driver* psMotor;

   int running = 0;
   std::thread actuationThread;
   void worker();
   int* pfds_read;


   
};