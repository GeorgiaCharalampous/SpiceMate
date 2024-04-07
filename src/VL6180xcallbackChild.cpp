#include <stdio.h>
#include <VL6180xcallbackChild.h>

void VL6180xcallbackChild::hasSample(int v){
	printf("Distance to object is %u mm. \n", v);  //Changing this had no effect on Segmentation Fault error.
};
