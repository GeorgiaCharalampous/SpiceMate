#ifndef VL6180x_rpi
#include "VL6180x_rpi.h"
#endif
// #ifndef VL6180xcallbackChild
// #include "VL6180xcallbackChild.h"
// #endif



int main(int argc, char *argv[]){
    
    VL6180x_rpi Sensor_Instance;
    VL6180xcallbackChild printCallback;

    uint8_t Range_Threshold_Low = 100;//mm
    uint8_t Range_Threshold_HIGH = 100; //mm
    uint8_t Range_Intermeasurement_period = 100; //ms
    uint8_t Range_Max_convergence_time = 15; //ms

    VL6180x_settings Settings_Struct;
    Settings_Struct.sysrange_thresh_low = 100;

    printf("Range threshold low is %u . \n",Settings_Struct.sysrange_thresh_low);
    
    Sensor_Instance.registerCallback(&printCallback);
    
    Sensor_Instance.startRangeContinuous(Settings_Struct);
    getchar();
	Sensor_Instance.stop();
	return 0;
    
}