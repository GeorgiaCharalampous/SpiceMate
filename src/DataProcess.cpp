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
	if ((value > lowerLimit)&&(value < upperLimit))
	{
		currentValueInRange = true;
	}
	else {currentValueInRange = false;};

	if(isDispensing)
	{
		counterStart = 0;
		if(!currentValueInRange){
			counterStop +=1;
		}
		else {counterStop = 0;};
		if(10==counterStop){
			printf("Stop Dispensing! \n");
			counterStop = 0;
			isDispensing = false;
		};

	};
	if(!isDispensing)
	{
		counterStop = 0;
		if(currentValueInRange){
			counterStart +=1;
		}
		else {counterStart = 0;};

		if(10 == counterStart){
			printf("Start Dispensing! \n");
			counterStart = 0;
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