#include <stdio.h>
#include <VL6180xcallbackChild.h>
#include <thread>

void VL6180xcallbackChild::hasSample(uint8_t sample){
	dp->value = sample;
	dp->dataReceived = true;
};