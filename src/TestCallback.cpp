#include <TestCallback.h>

void TestCallback::registerCallback(VL6180xcallback* cb){
    sensorCallback = cb;
};

void TestCallback::unregisterCallback(){
    sensorCallback = nullptr;
};

void TestCallback::CreateData(){
    printf("Create data begins \n");

    if(on) {
        value = value + 1;
    }

    sensorCallback->hasSample(value);
    printf("Value passed \n");
};

TestCallback::TestCallback(){
    bool on;
};

void TestCallback::setActive(){
    on = true;
};

void TestCallback::setInactive()
{
    on = false;
};

