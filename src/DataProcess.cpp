#ifndef DataProcess
#include <DataProcess.h>
#endif

void DataProcess::start(){
	running = true;
	prosThread = std::thread(&DataProcess::worker,this);
	#ifdef DEBUG
	printf("Data processing thread opened \n"); 	
	#endif
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
			#ifdef DEBUG
			printf("Stop Dispensing! \n");
			#endif
			bool status = false;
			if(processCallback != nullptr){
				processCallback->dataProcessed(status);
			}
			else {
				printf("Null pointer to callback! \n");
			};
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
			#ifdef DEBUG
			printf("Start Dispensing! \n");
			#endif
			bool status = true;
			if(processCallback != nullptr){
				processCallback->dataProcessed(status);
			}
			else {
				printf("Null pointer to callback! \n");
			};
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