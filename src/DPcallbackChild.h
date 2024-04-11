#ifndef  DPcallbackInterface
#include <DPcallbackInterface.h>
#endif

class DPcallbackChild : public DPcallbackInterface{
    virtual void dataProcessed(bool status);

};