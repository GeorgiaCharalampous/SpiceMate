#include <stdio.h>
#include <VL6180xcallbackChild.h>

virtual void VL6180xcallbackChild::hasSample(unit8_t v){
	printf("%e\n", v);
};
