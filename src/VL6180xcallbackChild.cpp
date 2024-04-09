#include <stdio.h>
#include <VL6180xcallbackChild.h>

void VL6180xcallbackChild::hasSample(uint8_t sample){
	printf("Distance to object is %u mm. \n", sample);  //Changing this had no effect on Segmentation Fault error.
};
