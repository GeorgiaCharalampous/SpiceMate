#define VIBRO_STATUS_REG        0x00        // ALL READ ONLY
#define VIBRO_MODE_REG          0x01        // [6] is Standby 0: Device ready 1: Standby(Default)
                                            // [2:0] is Mode 0:Internal trigger 3:PWM trigger 5:Real-time Playback 7:Autocalibration
#define VIBRO_RTP_REG           0x02
#define VIBRO_REGFIELD_REG      0x03        // 6:LRA Library
#define VIBRO_WAVESEQ_REG       0x04:0x0B   //[6:0] holds id of the waveform to be played by the vibro
#define VIBRO_GO_REG            0x0C        //[0] sets vibro to go and gives waveforms to sequencer

//Offset registers
#define VIBRO_ODT_OFFSET_REG    0x0D        //automatic for closed loop mode
#define VIBRO_SPT_OFFSET_REG    0x0E        
#define VIBRO_SNT_OFFSET_REG    0x0F        
#define VIBRO_BRT_OFFSET_REG    0x10        //automatic for closed-loop mode

//audio to haptic mode
#define VIBRO_ATH_REG           0x11
#define VIBRO_ATH_MIN_INPUT_REG 0x12
#define VIBRO_ATH_MAX_INPUT_REG 0x13
#define VIBRO_ATH_MIN_DRIVE_REG 0x14
#define VIBRO_ATH_MIN_DRIVE_REG 0x15

#define VIBRO_RATED_VOLTAGE_REG 0x16        //sets ref voltage for fullscale output needed by auto-cal
#define VIBRO_OD_CLAMP_REG      0x17
#define VIBRO_A_CAL_COMP_REG    0x18
#define VIBRO_A_CAL_BEMF_REG    0x19 
#define VIBRO_FEEDBACK_REG      0x1A        // all set before auto cal [7] 1:LRA mode [6:4] default 3 [3:2] default 1 [1:0] default 2
#define VIBRO_CONTROL1_REG      0x1B        // [5] 0:for PWM
#define VIBRO_CONTROL2_REG      0x1C
#define VIBRO_CONTROL3_REG      0x1D
#define VIBRO_CONTROL4_REG      0x1E
#define VIBRO_VBAT_REG          0x21
#define VIBRO_LRA_PERIOD_REG    0x22