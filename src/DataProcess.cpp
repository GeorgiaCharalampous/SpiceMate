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
		counterAbove = 0;
		if(!currentValueInRange){
			counterBelow +=1;
		}
		else {counterBelow = 0;};
		if(10==counterBelow){
			printf("Stop Dispensing! \n");
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

		if(10 == counterAbove){
			printf("Start Dispensing! \n");
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