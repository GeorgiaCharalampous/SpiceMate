#include <stdio.h>
#include <VL6180xcallbackChild.h>

void VL6180xcallbackChild::hasSample(uint8_t sample){

	if ((sample > lowerLimit)&&(sample < upperLimit)){
		counter +=1;
	}
	else {
		counter = 0;
	};

	if (10 == counter)
	{
		printf("Persistent value!"); 
		counter = 0;
		printf("Counter reset. Counter is %u mm. \n",counter); 
	};
};
