#ifndef DPcallbackChild 
#include <DPcallbackChild.h>
#endif
void DPcallbackChild::dataProcessed(bool status){
    if(pactuator == nullptr){
		throw "Null pointer to actuating class";
	};
    
    pactuator->activate = status;
    pactuator->dataReceived = true;
    write(*pfds_write,"1\n",1);
};