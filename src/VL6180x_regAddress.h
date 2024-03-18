
// registers for model identification
#define IDENTIFICATION_MODEL_ID             0x000           //default 0xB4
#define IDENTIFICATION_MODEL_REV_MAJOR      0x001
#define IDENTIFICATION_MODEL_REV_MINOR      0x002
#define IDENTIFICATION_MODULE_REV_MAJOR     0x003
#define IDENTIFICATION_MODULE_REV_MINOR     0x004
#define IDENTIFICATION_DATE_HI              0x006
#define IDENTIFICATION_DATE_LO              0x007
#define IDENTIFICATION_TIME                 0x008:0x009
// registers for system setup
#define SYSTEM_MODE_GPIO0                   0x010
#define SYSTEM_MODE_GPIO1                   0x011
#define SYSTEM_HISTORY_CTRL                 0x012
#define SYSTEM_INTERRUPT_CONFIG_GPIO        0x014
#define SYSTEM_INTERRUPT_CLEAR              0x015           //used for clear interrupts
#define SYSTEM_FRESH_OUT_OF_RESET           0x016           //used for initialisation func
#define SYSTEM_GROUPED_PARAMETER_HOLD       0x017
// registers for range setup
#define SYRANGE_START                       0x018
#define SYRANGE_THRESH_HIGH                 0x019
#define SYRANGE_THRESH_LOW                  0x01A
#define SYRANGE_INTERMEASUREMENT_PERIOD     0x01B
#define SYRANGE_MAX_CONVERGENCE_TIME        0x01C
#define SYRANGE_CROSSTALK_COMPENSATION_RATE 0x01E
#define SYRANGE_CROSSTALK_VALID_HEIGHT      0x021           //used for defaultCrosstalkValidHeight func
#define SYRANGE_EALRY_CONVERGENCE_ESTIMATE  0x022
#define SYRANGE_PART_TO_PART_RANGE_OFFSET   0x024           //used for ptp_offset
#define SYRANGE_RANGE_IGNORE_VALID_HEIGHT   0x025
#define SYRANGE_RANGE_IGNORE_THRESHOLD      0x026
#define SYRANGE_MAX_AMBIENT_LEVEL_MULT      0x02C
#define SYRANGE_RANGE_CHECK_ENABLES         0x02D           //used for rce var
#define SYRANGE_VHV_RECALIBRATE             0x02E
#define SYRANGE_VHV_REPEAT_RATE             0x031
#define SYSRANGE_SCALER                     0x096           //used for set scaling
// registers for ambient light source (ALS) setup
#define SYSALS_START                        0x038
#define SYSALS_THRESH_HIGH                  0x03A
#define SYSALS_THRESH_LOW                   0x03C
#define SYSALS_INTERMEASUREMENT_PERIOD      0x03E
#define SYSALS_ANALOGUE_GAIN                0x03F
#define SYSALS_INTEGRATION_PERIOD           0x040
// registers for resutls
#define RESULT_RANGE_STATUS                 0x04D
#define RESULT_ALD_STATUS                   0x04E
#define RESULT_INTERRUPT_STATUS_GPIO        0x04F           //used for poll (ex cd) and interrupt
#define RESULT_ALS_VAL                      0x050
#define RESULT_HISTORY_BUFFER_x             0x052:0x060
#define RESULT_RANGE_VAL                    0x062
#define RESULT_RANGE_RAW                    0x064
#define RESULT_RANGE_RETURN_RATE            0x066
#define RESULT_RANGE_REFERENCE_RATE         0x068
#define RESULT_RANGE_RETURN_SIGNAL_COUNT    0x06C
#define RESULT_RANGE_REFERENCE_SIGNAL_COUNT 0x070           // used also in interrupt func and clear interupts
#define RESULT_RANGE_RANGE_RETURN_AMB_COUNT 0x074
#define RESULT_RANGE_REFERENCE_AMB_COUNT    0x078
#define RESULT_RANGE_RETURN_CONV_TIME       0x07C
#define RESULT_RANGE_REFERENCE_CONV_TIME    0x080
// other registers
#define READOUT_AVERAGING_SAMPLE_PERIOD     0x10A
#define FIRMWARE_BOOTUP                     0x119
#define FIRMWARE_RESULT_SCALER              0x120
#define I2C_SLAVE_DEVICE_ADDRESS            0x212          // can change the default sensor address
#define INTERLEAVED_MODE_ENABLE             0x2A3