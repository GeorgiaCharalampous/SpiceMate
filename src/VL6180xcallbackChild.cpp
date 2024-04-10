#include <stdio.h>
#include <VL6180xcallbackChild.h>

void VL6180xcallbackChild::hasSample(uint8_t sample){
	if(dp == nullptr){
		throw "Null pointer to processing class";
	};
	//Passing the reading to the processing class
	dp->value = sample;
	dp->dataReceived = true;
};