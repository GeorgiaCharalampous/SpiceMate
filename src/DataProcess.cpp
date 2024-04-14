#ifndef DataProcess
#include <DataProcess.h>
#endif

void DataProcess::start(){
	running = true;
	prosThread = std::thread(&DataProcess::worker,this);
	printf("Data processing thread opened \n"); 
};

void DataProcess::worker(){
	while (1 == running){
		char dataReady;
		read(*pfds_read, &dataReady, sizeof(char));
		thresholding();
	}
};

void DataProcess::thresholding(){
    if (!dataReceived) return;
	dataReceived = false;
	
	//printf("Incomming reading: %u \n",value); 
	if ((value > lowerLimit)&&(value < upperLimit))
	{
		currentValueInRange = true;
	}
	else {
		currentValueInRange = false;
	};

	if(isDispensing)
	{
		counterAbove = 0;
		if(!currentValueInRange){
			counterBelow +=1;
		}
		else {
			counterBelow = 0;
		};
		if(5 == counterBelow){
			printf("Stop Dispensing! \n");
			bool status = false;
			processCallback->dataProcessed(status);
			counterBelow= 0;
			isDispensing = false;
		};

	};
	if(!isDispensing)
	{
		counterBelow = 0;
		if(currentValueInRange){
			counterAbove +=1;
		}
		else {counterAbove = 0;};

		if(30 == counterAbove){
			printf("Start Dispensing! \n");
			bool status = true;
			processCallback->dataProcessed(status);
			counterAbove = 0;
			isDispensing = true;
		};
	};
	lastValueInRange = currentValueInRange;
};

void DataProcess::stop(){
	
	if(!running) return;
	running = 0;
	prosThread.join();
	#ifdef DEBUG
	fprintf(stderr,"Processing thread stopped.\n");
    #endif	
}

void DataProcess::registerCallback(DPcallback* cb){
    processCallback = cb;
};

void DataProcess::unRegisterCallback()
{
	processCallback = nullptr;
};