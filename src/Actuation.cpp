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
        pvMotor->playHaptic_realTime();
    }
};