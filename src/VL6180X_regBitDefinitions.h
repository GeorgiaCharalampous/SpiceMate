#ifndef stdint
#include <stdint.h>
#endif

//SYSTEM__MODE_GPIO1
enum {
    RESET_MODE_GPIO1            = 0x60,
    ACTIVE_HIGH                 = 0b00100000,
    ACTIVE_LOW                  = 0b00000000,
    OFF_MODE_GPIO1              = 0b00000000,
    GPIO_INTERRUPT_OUTPUT       = 0b00010000,
};

//SYSTEM_INTERRUPT_CONFIG_GPIO
enum {
    RESET_CONFIG_GPIO           = 0x0,
    ALS_LEVEL_LOW               = 0b00001000,
    ALS_LEVEL_HIGH              = 0b00010000,
    ALS_OUT_OF_WINDOW           = 0b00011000,
    ALS_NEW_SAMPLE_READY        = 0b00100000,
    RANGE_LEVEL_LOW             = 0b00000001,
    RANGE_LEVEL_HIGH            = 0b00000010,
    RANGE_OUT_OF_WINDOW         = 0b00000011,
    RANGE_NEW_SAMPLE_READY      = 0b00000100,
};

// SYSTEM_INTERRUPT_CLEAR
enum {
    RESET_INTERRUPT_CLEAR       = 0x0,
    CLEAR_RANGE_INT             = 0b00000001,
    CLEAR_ALS_INT               = 0b00000010,
    CLEAR_ERROR_INT             = 0b00000100,
};

// SYSRANGE_START
enum {
    RANGING_MODE_SINGLE_SHOT    = 0b00000000,
    RANGING_MODE_CONTINUOUS     = 0b00000010,
    RANGE_START_STOP_TRIGGER    = 0b00000001,
};

// SYSALS_START
enum {
    ALS_MODE_SINGLE_SHOT        = 0b00000000,
    ALS_MODE_CONTINUOUS         = 0b00000010,
    ALS_START_STOP_TRIGGER      = 0b00000001,
};

// SYSALS_ANALOGUE_GAIN
enum {
    RESET_ALS_GAIN              = 0x06,
    ALS_GAIN_20                 = 0b01000000,
    ALS_GAIN_10                 = 0b01000001,
    ALS_GAIN_5                  = 0b01000010,
    ALS_GAIN_2_5                = 0b01000011,
    ALS_GAIN_1_67               = 0b01000100,
    ALS_GAIN_1_25               = 0b01000101,
    ALS_GAIN_1                  = 0b01000110,
    ALS_GAIN_40                 = 0b01000111,
};


// SYSRANGE__RANGE_CHECK_ENABLES
enum {
    RESET_RANGE_CHECK_ENABLES   = 0x11,
    SIGNAL_TO_NOISE_ENABLE      = 0b00010000,
    RANGE_IGNORE_ENABLE         = 0b00000010,
    EARLY_CONVERGENCE_ENABLE    = 0b00000001,
};