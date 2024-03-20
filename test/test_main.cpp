#include "src/VL6180x_rpi.h"
#include "src/VL6180xcallbackChild.h"



int main(int argc, char *argv[]){
    
    VL6180x_rpi Sensor_Instance;
    
    uint8_t Range_Threshold_Low = 100;//mm
    uint8_t Range_Threshold_HIGH = 100; //mm
    uint8_t Range_Intermeasurement_period = 100; //ms
    uint8_t Range_Max_convergence_time = 15; //ms

    range_thresh_low = &Range_Threshold_Low;
    range_thresh_high = &Range_Threshold_HIGH;
    intermeasurement_period = &Range_Intermeasurement_period;
    max_convergence_time = &Range_Max_convergence_time;

    VL6180x_settings Settings_Struct;
    printf("Range threshold low is %f",Settings_Struct.sysrange_thresh_low);


}