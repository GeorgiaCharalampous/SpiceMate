#include <DataProcess.h>

void DataProcess::start(){
	running = true;
	prosThread = std::thread(&DataProcess::worker,this);
};

void DataProcess::worker(){
	while (running){
		thresholding();
	}
};

void DataProcess::thresholding(){
    if (!dataReceived) return;
	
	printf("Incomming reading: %u \n",value); 
    if ((value > lowerLimit)&&(value< upperLimit)){
		counter +=1;
	}
	else {
		counter = 0;
	};

	if (10 == counter)
	{
		printf("Start Dispensing! \n"); 
		counter = 0;
	};

};

void DataProcess::stop(){
	if(!running) return;
	running = 0;
	prosThread.join();
	#ifdef DEBUG
	fprintf(stderr,"Processing thread stopped.\n");
    #endif	
}