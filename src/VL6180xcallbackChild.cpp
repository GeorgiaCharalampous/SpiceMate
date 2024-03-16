#include <stdio.h>
#include <VL6180xcallbackChild.h>

void VL6180xcallbackChild::hasSample(uint8_t v){
	printf("%e\n", v);
};
