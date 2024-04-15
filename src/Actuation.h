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
   Actuation(VIBRO4_rpi* VibroMotor,Servo_Driver* ServoMotor);

   /**
    * Destructor
    **/ 
   ~Actuation();

    /**
    * Sets a pointer to a file descriptor to be used
    * for read() blocking
    * \param a pointer to an existing descriptor
    **/
   void setFileDescriptor(int* a){
        pfds_read = a;
    };

    /**
     * Boolean to describe if the motors should be activated
     * Motors are powered off by default
     **/
   bool activate = false;

   /**
    * Boolean to indicate if data has been received
    * and the states of the motors required changing
   **/
   bool dataReceived = false;

   private:
   /**
    * Pointer to the vibrational motor 
   **/
   VIBRO4_rpi* pvMotor;

   /**
    * Pointer to the servo motor 
   **/
   Servo_Driver* psMotor;

   /**
    * Current state of the class
   **/
   int running = 0;

   /**
    * Actuation thread 
   **/
   std::thread actuationThread;

   /**
    * Worker function of the actuation thread.
    * Blocked until data is read from the file descriptor 
   **/
   void worker();

   /**
    * Pointer to a file descriptor to read from.
    * For blocking the thread until data is received .
    * Initially a nullptr. Must be set using
    * setFileDescriptor()
    **/
   int* pfds_read = nullptr;

   /**
    * Current status of the actuator
    * True if the motors are on
    * False otherwise 
   **/

   bool status = false;
};