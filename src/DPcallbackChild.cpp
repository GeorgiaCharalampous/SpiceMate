#ifndef DPcallbackChild 
#include <DPcallbackChild.h>
#endif
void DPcallbackChild::dataProcessed(bool status){
    if(pactuator == nullptr){
		throw "Null pointer to motor class";
	};
    
    pactuator->activate = status;
    write(*pfds_write,"1\n",1);
};