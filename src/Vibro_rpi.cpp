#ifndef Vibro4_rpi
#include "Vibro4_rpi.h"
#endif

#include <fcntl.h>
#include <sys/ioctl.h>

#include <bitset>

void VIBRO4_rpi::initVibro(VIBRO4_settings settings){
        
        motorSettings = settings;

        char gpioFilename[20]; // character array meant to hold the i2c device name
	    snprintf(gpioFilename, 19, "/dev/i2c-%d", settings.default_i2c_bus); // add name to the buffer created
	    fd_i2c = open(gpioFilename, O_RDWR);
	    if (fd_i2c < 0) {
	        char i2copen[] = "Could not open I2C.\n";

        #ifdef DEBUG
            fprintf(stderr, i2copen);
        #endif
    	        throw i2copen;
	    }

    	if (ioctl(fd_i2c, I2C_SLAVE, settings.address) < 0) {
	        char i2cslave[] = "Could not access I2C adress.\n";
        #ifdef DEBUG
            fprintf(stderr,i2cslave);
        #endif
            throw i2cslave;
        }

        #ifdef DEBUG
            fprintf(stderr, "Init.\n");
        #endif

        chipDRDY = gpiod_chip_open_by_number(settings.drdy_chip);
        pinDRDY = gpiod_chip_get_line(chipDRDY,settings.drdy_gpio);

        gpiod_line_request_output(pinDRDY,"example1",0); // open the pin to drive as output
        gpiod_line_set_value(pinDRDY,1); // sets EN pin to high 

    // Set default regs
    /*
    i2c_writeByte(VIBRO_STATUS_REG,DEFAULT_STATUS);
    i2c_writeByte(VIBRO_MODE_REG,STANDBY);
    i2c_writeByte(VIBRO_RTP_REG,0x00);
    i2c_writeByte(VIBRO_REGFIELD_REG,LIBRARY_SELECT_LRA);
    i2c_writeByte(VIBRO_WAV_SEQ_REG1,0x00);
    i2c_writeByte(VIBRO_WAV_SEQ_REG2,0x00);
    i2c_writeByte(VIBRO_WAV_SEQ_REG3,0x00);
    i2c_writeByte(VIBRO_WAV_SEQ_REG4,0x00);
    i2c_writeByte(VIBRO_WAV_SEQ_REG5,0x00);
    i2c_writeByte(VIBRO_WAV_SEQ_REG6,0x00);
    i2c_writeByte(VIBRO_WAV_SEQ_REG7,0x00);
    i2c_writeByte(VIBRO_WAV_SEQ_REG8,0x00);
    i2c_writeByte(VIBRO_GO_REG,VIBRO_STOP);
    i2c_writeByte(VIBRO_ODT_OFFSET_REG,0x00);
    i2c_writeByte(VIBRO_SPT_OFFSET_REG,0x00);
    i2c_writeByte(VIBRO_SNT_OFFSET_REG,0x00);
    i2c_writeByte(VIBRO_BRT_OFFSET_REG,0x00);
    i2c_writeByte(VIBRO_ATH_REG,);
    */
        // wait before sending i2c commands for motor init
        usleep(260);

        // Initialise and autocallibrate
        i2c_writeByte(VIBRO_MODE_REG,settings.rdy_internalTrig); // decide on whether we need both
        i2c_writeByte(VIBRO_MODE_REG,settings.init_autocal_mode); 
        i2c_writeByte(VIBRO_FEEDBACK_REG,settings.init_feedBack_reg);
        i2c_writeByte(VIBRO_RATED_VOLTAGE_REG,settings.init_ratedVoltage_reg);
        i2c_writeByte(VIBRO_OD_CLAMP_REG,settings.init_odClamp_reg);
        i2c_writeByte(VIBRO_CONTROL4_REG,settings.init_autocal_mode);    
        i2c_writeByte(VIBRO_CONTROL1_REG,settings.init_control1_reg);
        i2c_writeByte(VIBRO_CONTROL2_REG,settings.init_control2_reg);
        i2c_writeByte(VIBRO_GO_REG,settings.init_go);
        i2c_writeByte(VIBRO_REGFIELD_REG,settings.vibro_library);

        if (i2c_readByte(VIBRO_STATUS_REG)==DIAG_RESULT_FAIL){
                #ifdef DEBUG
                fprintf(stderr, "Auto-calibration failed.\n");
                #endif
                throw "Auto-calibration failed";
        };

        /* preset the sequences
        i2c_writeByte(VIBRO_WAV_SEQ_REG1,0x01);
        i2c_writeByte(VIBRO_WAV_SEQ_REG2,0xC);
        i2c_writeByte(VIBRO_WAV_SEQ_REG3,0xE);
        i2c_writeByte(VIBRO_WAV_SEQ_REG4,0x00);
        i2c_writeByte(VIBRO_WAV_SEQ_REG5,0x00);
        i2c_writeByte(VIBRO_WAV_SEQ_REG6,0x00);
        i2c_writeByte(VIBRO_WAV_SEQ_REG7,0x00);
        i2c_writeByte(VIBRO_WAV_SEQ_REG8,0x00);
        */

        // put on standby for low pwer mode
        i2c_writeByte(VIBRO_MODE_REG,settings.standby); // also sets this to internal trigger
}

void VIBRO4_rpi::playHaptic_preDef(){
        
        // Wake up and set to internal trigger
        i2c_writeByte(VIBRO_MODE_REG,MODE_INT_TRIGGER); 
        // wake up and set to external trigger
//        i2c_writeByte(VIBRO_MODE_REG,MODE_EXT_TRIGGER_EDGE);

        // Haptic sequence for internal trigger
        i2c_writeByte(VIBRO_WAV_SEQ_REG1,0x01);
        i2c_writeByte(VIBRO_WAV_SEQ_REG2,0xC);
        i2c_writeByte(VIBRO_WAV_SEQ_REG3,0xE);
        i2c_writeByte(VIBRO_WAV_SEQ_REG4,0x00);
        i2c_writeByte(VIBRO_WAV_SEQ_REG5,0x00);
        i2c_writeByte(VIBRO_WAV_SEQ_REG6,0x00);
        i2c_writeByte(VIBRO_WAV_SEQ_REG7,0x00);
        i2c_writeByte(VIBRO_WAV_SEQ_REG8,0x00);

        i2c_writeByte(VIBRO_GO_REG,VIBRO_GO);
}

void VIBRO4_rpi::playHaptic_realTime(){
        
        // Wake up and set to internal trigger
        i2c_writeByte(VIBRO_MODE_REG,MODE_RTPLAYBACK); 
        // wake up and set to external trigger
//        i2c_writeByte(VIBRO_MODE_REG,MODE_EXT_TRIGGER_EDGE);

}

// i2c read and write protocols
void VIBRO4_rpi::i2c_writeByte(uint8_t reg, unsigned data)
{
	uint8_t tmp[3];
	tmp[0] = reg;
	tmp[1] = (char)((data & 0xff00) >> 8);
	tmp[2] = (char)(data & 0x00ff);
	long int r = write(fd_i2c,&tmp,3);
        if (r < 0) {
        #ifdef DEBUG
                fprintf(stderr,"Could not write word from %02x. ret=%d.\n",motorSettings.address,r);
        #endif
                throw "Could not write to i2c.";
        }
}

unsigned VIBRO4_rpi::i2c_readByte(uint8_t reg)
{
	uint8_t tmp[2];
	tmp[0] = reg;
	write(fd_i2c,&tmp,1);
        long int r = read(fd_i2c, tmp, 2);
        if (r < 0) {
        #ifdef DEBUG
                fprintf(stderr,"Could not read word from %02x. ret=%d.\n",motorSettings.address,r);
        #endif
                throw "Could not read from i2c.";
        }
        return (((unsigned)(tmp[0])) << 8) | ((unsigned)(tmp[1]));
}

int VIBRO4_rpi::i2c_readConversion()
{
	const int reg = 0;
	char tmp[3];
	tmp[0] = reg;
	write(fd_i2c,&tmp,1);
        long int r = read(fd_i2c, tmp, 2);
        if (r < 0) {
        #ifdef DEBUG
                fprintf(stderr,"Could not read ADC value. ret=%d.\n",r);
        #endif
                throw "Could not read from i2c.";
        }
        return ((int)(tmp[0]) << 8) | (int)(tmp[1]);
}