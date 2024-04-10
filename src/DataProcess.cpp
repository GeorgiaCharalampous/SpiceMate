#include <DataProcess.h>

void DataProcess::thresholding(){
    if (!dataReceived) return;

    if ((value > lowerLimit)&&(value< upperLimit)){
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

};