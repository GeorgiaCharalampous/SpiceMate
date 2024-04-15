#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef  VL6180xcallbackChild
#include <VL6180xcallbackChild.h>
#endif


class TestCallback{
    public:
    TestCallback();

    void setActive();
    void setInactive();
    void registerCallback(VL6180xcallback* cb);
    void CreateData();
    bool getStatus(){return on;}

    private:

    bool on;
    int8_t value = 0;
    VL6180xcallback* sensorCallback = nullptr;
   
    void unregisterCallback();

};