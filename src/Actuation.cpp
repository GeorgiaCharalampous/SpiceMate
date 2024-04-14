#include<Actuation.h>

Actuation::Actuation(VIBRO4_rpi* VibroMotor,Servo_Driver* ServoMotor,int* FD){
    pvMotor = VibroMotor;
    psMotor = ServoMotor;
    pfds_read = FD;


    #ifdef DEBUG
	fprintf(stderr,"Motor thread started.\n");
    #endif	
    running = 1;
	actuationThread = std::thread(&Actuation::worker,this);
};

void Actuation::worker(){
    while(1 == running){
        char dataReady;
        read(*pfds_read, &dataReady, sizeof(char));
        if(activate){
            psMotor->startPWM();
            pvMotor->playHaptic_realTime();

        }
        else{
            pvMotor->stopHaptic();
            psMotor->stopPWM();
        };
        
    }
};

Actuation::~Actuation(){
    if(!running) return;
    running = 0;
    actuationThread.join();
    pvMotor->~VIBRO4_rpi();
    psMotor->~Servo_Driver();
    #ifdef DEBUG
	fprintf(stderr,"Motor thread stopped.\n");
    #endif	
};