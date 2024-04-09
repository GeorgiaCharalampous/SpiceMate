#include <stdio.h>
#include <VL6180xcallbackChild.h>
#include <DataProcess.h>
#include <thread>

void VL6180xcallbackChild::hasSample(uint8_t sample){

    if ((sample> lowerLimit)&&(sample < upperLimit)){
		counter +=1;
	}
	else {
		counter = 0;
	};

	if (10 == counter)
	{
		printf("Start Dispensing!"); 
		counter = 0;
	};
    

	//processThread = std::thread(&DataProcess::worker,this);

};