#ifndef VL6180x_rpi
#include "VL6180x_rpi.h"
#endif
// #ifndef VL6180xcallbackChild
// #include "VL6180xcallbackChild.h"
// #endif



int main(int argc, char *argv[]){
    
    VL6180x_rpi Sensor_Instance;
    VL6180xcallbackChild printCallback;

    int Range_Threshold_Low = 100;//mm
    int Range_Threshold_HIGH = 100; //mm
    int Range_Intermeasurement_period = 100; //ms
    int Range_Max_convergence_time = 15; //ms

    VL6180x_settings Settings_Struct;
    Settings_Struct.sysrange_thresh_low = 100;
    Settings_Struct.sysrange_thresh_low = 128;

    printf("Range threshold low is %u . \n",Settings_Struct.sysrange_thresh_low);

    // Sensor_Instance.registerCallback(&printCallback);
    // Sensor_Instance.startRangeContinuous(Settings_Struct);
    // for(int i = 0; i < 1000000; i++){
    //     Sensor_Instance.getStatus();
    // }
    // printf("Done \n");
    // Sensor_Instance.stop();
    // printf("Test finished \n");
    // return 0;
    
    Sensor_Instance.registerCallback(&printCallback);
    Sensor_Instance.startRangeContinuous(Settings_Struct);
    printf("Acquisisition started \n");
    getchar();
    printf("Character gotten \n");
	Sensor_Instance.stop();
    printf("Test finished \n");
	return 0;
    
}