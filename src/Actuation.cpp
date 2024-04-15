#include<Actuation.h>

Actuation::Actuation(VIBRO4_rpi* VibroMotor,Servo_Driver* ServoMotor){
    pvMotor = VibroMotor;
    psMotor = ServoMotor;

    pvMotor->setAmplitude(100);
    psMotor->setFrequency(50);

    running = 1;
	actuationThread = std::thread(&Actuation::worker,this);
    #ifdef DEBUG
	fprintf(stderr,"Motor thread started.\n");
    #endif	
};

void Actuation::worker(){
    while(1 == running){
        char dataReady;
        read(*pfds_read, &dataReady, sizeof(char));
        if(dataReceived){
            dataReceived = false;
            if(activate){
                psMotor->setAngle(180);
                psMotor->startPWM();
                pvMotor->playHaptic_realTime();
            }
            else{
                pvMotor->stopHaptic();
                psMotor->setAngle(0);
            }
        };
    }
};

Actuation::~Actuation(){
    if(!running) return;
    running = 0;
    actuationThread.join();
    psMotor->setAngle(0);
    psMotor->stopPWM();
    #ifdef DEBUG
	fprintf(stderr,"Motor thread stopped.\n");
    #endif	
};