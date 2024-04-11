#include <DPcallbackChild.h>

void DPcallbackChild::dataProcessed(bool status){
    if(vmotor == nullptr){
		throw "Null pointer to motor class";
	};
    
    vmotor->activate=status;
    vmotor->changedState = true;
};