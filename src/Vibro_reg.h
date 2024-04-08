#ifndef stdint.h
#include <stdint.h>
#endif

//Registers for Vibro 4
#define VIBRO_STATUS_REG        0x00        // ALL READ ONLY
enum{
    DEFAULT_STATUS              = 0b01100000,
    DIAG_RESULT_FAIL            = 0b01101000,
};
#define VIBRO_MODE_REG          0x01       
//settings
enum {
    DEV_RESET                   = 0b10000000,
    STANDBY                     = 0b01000000,
    DEVICE_RDY                  = 0b00000000,
    MODE_INT_TRIGGER            = 0b00000000,
    MODE_EXT_TRIGGER_EDGE       = 0b00000001,
    MODE_EXT_TRIGGER_LVL        = 0b00000010,
    MODE_PWM_TRIG               = 0b00000011,
    MODE_RTPLAYBACK             = 0b00000101,
    MODE_DIAGNOSTIC             = 0b00000110,
    MODE_AUTO_CALIBRATION       = 0b00000111,
};

#define VIBRO_RTP_REG           0x02
#define VIBRO_REGFIELD_REG      0x03        
enum {
    HIGH_IMP_STATE_DIS          = 0b00000000,
    HIGH_IMP_STATE_ENABLE       = 0b00001000,
    LIBRARY_SELECT_LRA          = 0b00000110, //lib 6 for LRA
};

#define VIBRO_WAV_SEQ_REG1      0x04
#define VIBRO_WAV_SEQ_REG2      0x05
#define VIBRO_WAV_SEQ_REG3      0x06
#define VIBRO_WAV_SEQ_REG4      0x07
#define VIBRO_WAV_SEQ_REG5      0x08
#define VIBRO_WAV_SEQ_REG6      0x09
#define VIBRO_WAV_SEQ_REG7      0x0A
#define VIBRO_WAV_SEQ_REG8      0x0B
enum {
    WAIT_DEFAULT                = 0b00000000,
    WAIT_ENABLE                 = 0b10000000, // sets waveform sequencer to idle and delay is added between vibrations
    WAV_FRM_SEQ                 = 0b00000000, // holds the waveform identifier of the waveform to be played
};

#define VIBRO_GO_REG            0x0C        //[0] sets vibro to go and gives waveforms to sequencer
enum{
    VIBRO_GO                    = 0b00000001,
    VIBRO_STOP                  = 0b00000000,
};

//Offset registers
#define VIBRO_ODT_OFFSET_REG    0x0D        //automatic for closed loop mode
#define VIBRO_SPT_OFFSET_REG    0x0E        
#define VIBRO_SNT_OFFSET_REG    0x0F        
#define VIBRO_BRT_OFFSET_REG    0x10        //automatic for closed-loop mode

//audio to haptic mode NA
#define VIBRO_ATH_REG           0x11
#define VIBRO_ATH_MIN_INPUT_REG 0x12
#define VIBRO_ATH_MAX_INPUT_REG 0x13
#define VIBRO_ATH_MIN_DRIVE_REG 0x14
#define VIBRO_ATH_MIN_DRIVE_REG 0x15

#define VIBRO_RATED_VOLTAGE_REG 0x16        //sets ref voltage for fullscale output needed by auto-cal
enum{
    RATED_VOLTAGE_DEFAULT       = 0b00111111,
    RATED_VOLTAGE_170Hz         = 0b01101000,
};

#define VIBRO_OD_CLAMP_REG      0x17
enum{
    OD_CLAMP_DEFAULT            = 0b10001001,// 3V
    OD_CLAMP_MOTOR              = 0b01111111 // 2.8V
};
#define VIBRO_A_CAL_COMP_REG    0x18
enum{
    A_CAL_COMP                  = 0b00001101,
};
#define VIBRO_A_CAL_BEMF_REG    0x19 
enum{
    A_CAL_BEMF                  = 0b01101101,
};
#define VIBRO_FEEDBACK_REG      0x1A        
enum{
    ERM_MODE                    = 0b00000000,
    LRA_MODE                    = 0b10000000,
    
    FB_BRAKE_FACTOR_1x          = 0b00000000,
    FB_BRAKE_FACTOR_2x          = 0b00010000,
    FB_BRAKE_FACTOR_3x          = 0b00100000,
    FB_BRAKE_FACTOR_4x          = 0b00110000, //default
    FB_BRAKE_FACTOR_6x          = 0b01000000,
    FB_BRAKE_FACTOR_8x          = 0b01010000,
    FB_BRAKE_FACTOR_16x         = 0b01100000,
    FB_BRAKE_DIS                = 0b01110000,
    
    LOOP_GAIN_LOW               = 0b00000000,
    LOOP_GAIN_MED               = 0b00000100, //default
    LOOP_GAIN_HIGH              = 0b00001000,
    LOOP_GAIN_VERY_HIGH         = 0b00010100,
    
    BEMF_GAIN_LRA_5x            = 0b00000000,
    BEMF_GAIN_LRA_10x           = 0b00000001,
    BEMF_GAIN_LRA_20x           = 0b00000010, //default
    BEMF_GAIN_LRA_30x           = 0b00000000,
}
#define VIBRO_CONTROL1_REG      0x1B        
enum{
    STARTUP_BOOST               = 0b10000000,
    AC_COUPLE_DIS               = 0b00000000, // for dc coupling or digital input modes
    AC_COUPLE_ENBL              = 0b00100000, //for ac coupling enabled
    DRIVE_TIME                  = 0b00010011
};

#define VIBRO_CONTROL2_REG      0x1C
enum{
    INPUT_MODE_UNIDIR           = 0b00000000,
    INPUT_MODE_BIDIR            = 0b10000000,
    BRAKE_STABILISER            = 0b01000000,
    
    SAMPLE_TIME_150um           = 0b00000000,
    SAMPLE_TIME_200um           = 0b00010000,
    SAMPLE_TIME_250um           = 0b00100000,
    SAMPLE_TIME_300um           = 0b00110000, //DEFAULT
    
    BLANKING_TIME               = 0b00000100,
    
    IDISS_TIME                  = 0b00000001
};

#define VIBRO_CONTROL3_REG      0x1D
enum{
    NG_THRESH_DIS               = 0b00000000,
    NG_THRESH_2pcnt             = 0b01000000,
    NG_THRESH_4pcnt             = 0b10000000, //DEFAULT
    NG_THRESH_8pcnt             = 0b11000000,
    
    ERM_OPEN_LOOP               = 0b00100000, //DEFAULT N/A
    
    SUPPLY_COMP_ENB             = 0b00000000,
    SUPPLY_COMP_DIS             = 0b00010000,
    
    DATA_FORMAT_RTP_SNG         = 0b00000000, 
    DATA_FORMAT_RTP_USGN        = 0b00001000,
    
    LRA_DRIVE_MODE_1            = 0b00000000,
    LRA_DRIVE_MODE_2            = 0b00000010,
    
    INPUT_MODE_PWM              = 0b00000000,
    INPUT_MODE_ANALOG           = 0b00000010,
    
    LRA_OPEN_LOOP               = 0b00000000,
    LRA_CLOSED_LOOP             = 0b00000001             
};

#define VIBRO_CONTROL4_REG      0x1E
enum{
    AUTO_CAL_TIME_150um         = 0b00000000,
    AUTO_CAL_TIME_250um         = 0b00010000,
    AUTO_CAL_TIME_500um         = 0b00100000, //default
    AUTO_CAL_TIME_1000um        = 0b00110000,
    OTP_STATUS_PROG             = 0b00000000,
    OTP_STATUS_NOTPROG          = 0b00000100,
    OTP_PROGRAM                 = 0b00000000
};

#define VIBRO_VBAT_REG          0x21
enum{
    VIBAT                       = 0b00000000,
};

#define VIBRO_LRA_PERIOD_REG    0x22
enum{
    LRA_PERIOD                  = 0b00000000,
};