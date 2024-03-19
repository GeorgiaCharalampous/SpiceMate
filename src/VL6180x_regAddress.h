// registers for model identification
#define SENSOR_IDENTIFICATION_MODEL_ID             0x000           //default 0xB4
#define SENSOR_IDENTIFICATION_MODEL_REV_MAJOR      0x001
#define SENSOR_IDENTIFICATION_MODEL_REV_MINOR      0x002
#define SENSOR_IDENTIFICATION_MODULE_REV_MAJOR     0x003
#define SENSOR_IDENTIFICATION_MODULE_REV_MINOR     0x004
#define SENSOR_IDENTIFICATION_DATE_HI              0x006
#define SENSOR_IDENTIFICATION_DATE_LO              0x007
#define SENSOR_IDENTIFICATION_TIME                 0x008:0x009

// registers for system setup
#define SENSOR_SYSTEM_MODE_GPIO0                   0x010
#define SENSOR_SYSTEM_MODE_GPIO1                   0x011

/*
struct systemMode_GPIO1 {
    uint8_t     reserved_bit0: 1;
    uint8_t     select:4;
    uint8_t     polarity:1;
    uint8_t     reserved_bit6_7:2;   
}
*/

#define SENSOR_SYSTEM_HISTORY_CTRL                 0x012
#define SENSOR_SYSTEM_INTERRUPT_CONFIG_GPIO        0x014
/*
struct interruptConfig {
    uint8_t     range_interrupt_mode:3;
    uint8_t     als_interrupt_mode:3;
    uint8_t     reserved_bits:2;
}
*/

#define SENSOR_SYSTEM_INTERRUPT_CLEAR              0x015           //used for clear interrupts
/*
struct interruptClear{
    uint8_t     clearSignal:3;
    uint8_t     reservedBits:5;
}*/

#define SENSOR_SYSTEM_FRESH_OUT_OF_RESET           0x016           //used for initialisation func
#define SENSOR_SYSTEM_GROUPED_PARAMETER_HOLD       0x017

// registers for range setup
#define SENSOR_SYRANGE_START                       0x018

/*
struct rangeStart{
    uint8_t     startstop:1;
    uint8_t     select:1;
    uint8_t     reservedBits:6;
}*/

#define SENSOR_SYRANGE_THRESH_HIGH                 0x019
#define SENSOR_SYRANGE_THRESH_LOW                  0x01A
#define SENSOR_SYRANGE_INTERMEASUREMENT_PERIOD     0x01B
#define SENSOR_SYRANGE_MAX_CONVERGENCE_TIME        0x01C
#define SENSOR_SYRANGE_CROSSTALK_COMPENSATION_RATE 0x01E
#define SENSOR_SYRANGE_CROSSTALK_VALID_HEIGHT      0x021           //used for defaultCrosstalkValidHeight func
#define SENSOR_SYRANGE_EALRY_CONVERGENCE_ESTIMATE  0x022
#define SENSOR_SYRANGE_PART_TO_PART_RANGE_OFFSET   0x024           //used for ptp_offset
#define SENSOR_SYRANGE_RANGE_IGNORE_VALID_HEIGHT   0x025
#define SENSOR_SYRANGE_RANGE_IGNORE_THRESHOLD      0x026
#define SENSOR_SYRANGE_MAX_AMBIENT_LEVEL_MULT      0x02C
#define SENSOR_SYRANGE_RANGE_CHECK_ENABLES         0x02D           //used for rce var
#define SENSOR_SYRANGE_VHV_RECALIBRATE             0x02E
#define SENSOR_SYRANGE_VHV_REPEAT_RATE             0x031
#define SENSRO_SYSRANGE_SCALER                     0x096           //used for set scaling

// registers for ambient light source (ALS) setup
#define SENSOR_SYSALS_START                        0x038

/*
struct rangeStart{
    uint8_t     startstop:1;
    uint8_t     select:1;
    uint8_t     reservedBits:6;
}*/

#define SENSOR_SYSALS_THRESH_HIGH                  0x03A
#define SENSOR_SYSALS_THRESH_LOW                   0x03C
#define SENSOR_SYSALS_INTERMEASUREMENT_PERIOD      0x03E
#define SENSOR_SYSALS_ANALOGUE_GAIN                0x03F
#define SENSOR_SYSALS_INTEGRATION_PERIOD           0x040

// registers for resutls
#define SENSOR_RESULT_RANGE_STATUS                 0x04D
#define SENSOR_RESULT_ALD_STATUS                   0x04E
#define SENSOR_RESULT_INTERRUPT_STATUS_GPIO        0x04F           //used for poll (ex cd) and interrupt
#define SENSOR_RESULT_ALS_VAL                      0x050
#define SENSOR_RESULT_HISTORY_BUFFER_x             0x052:0x060
#define SENSOR_RESULT_RANGE_VAL                    0x062
#define SENSOR_RESULT_RANGE_RAW                    0x064
#define SENSOR_RESULT_RANGE_RETURN_RATE            0x066
#define SENSOR_RESULT_RANGE_REFERENCE_RATE         0x068
#define SENSOR_RESULT_RANGE_RETURN_SIGNAL_COUNT    0x06C
#define SENSOR_RESULT_RANGE_REFERENCE_SIGNAL_COUNT 0x070           // used also in interrupt func and clear interupts
#define SENSOR_RESULT_RANGE_RANGE_RETURN_AMB_COUNT 0x074
#define SENSOR_RESULT_RANGE_REFERENCE_AMB_COUNT    0x078
#define SENSOR_RESULT_RANGE_RETURN_CONV_TIME       0x07C
#define SENSOR_RESULT_RANGE_REFERENCE_CONV_TIME    0x080

// other registers
#define SENSOR_READOUT_AVERAGING_SAMPLE_PERIOD     0x10A
#define SENSOR_FIRMWARE_BOOTUP                     0x119
#define SENSOR_FIRMWARE_RESULT_SCALER              0x120
#define SENSOR_I2C_SLAVE_DEVICE_ADDRESS            0x212          // can change the default sensor address
#define SENSOR_INTERLEAVED_MODE_ENABLE             0x2A3

/* Robot headers
#define VL6180X_ID                                    0xB4

#define VL6180X_NO_ERR                                0x00
#define VL6180X_EARLY_CONV_ERR                        0x06
#define VL6180X_MAX_CONV_ERR                          0x07
#define VL6180X_IGNORE_ERR                            0x08
#define VL6180X_MAX_S_N_ERR                           0x0B
#define VL6180X_RAW_Range_UNDERFLOW_ERR               0x0C
#define VL6180X_RAW_Range_OVERFLOW_ERR                0x0D
#define VL6180X_Range_UNDERFLOW_ERR                   0x0E
#define VL6180X_Range_OVERFLOW_ERR                    0x0F

#define VL6180X_DIS_INTERRUPT        0
#define VL6180X_HIGH_INTERRUPT       1
#define VL6180X_LOW_INTERRUPT        2

#define VL6180X_INT_DISABLE          0
#define VL6180X_LEVEL_LOW            1
#define VL6180X_LEVEL_HIGH           2
#define VL6180X_OUT_OF_WINDOW        3
#define VL6180X_NEW_SAMPLE_READY     4
*/

//Settings
#define SENSOR_defaultID            0xB4

#define GPIO1_highInterrupt         0x10
#define GPIO1_lowInterrupt          0x30

#define interruptConfig_Dis         0x00
#define interruptConfig_Low         0x01
#define interruptConfig_High        0x02                
#define interruptConfig_OfW         0x03
#define interruptConfig_Rdy         0x04

#define interruptClear_Range        0x00
#define interruptClear_ALS          0x01
#define interruptClear_Error        0x02

#define singleMode                  0x01
#define continuousMode              0x03
