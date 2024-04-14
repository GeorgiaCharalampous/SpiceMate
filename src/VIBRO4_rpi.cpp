#ifndef VIBRO4_rpi
#include "VIBRO4_rpi.h"
#endif

#include <bitset>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

void VIBRO4_rpi::initVibro(VIBRO4_settings settings){
        
        motorSettings = settings;
        printf("Motor initialisation begins\n");

        chipEN = gpiod_chip_open_by_number(settings.EN_chip);
        pinEN = gpiod_chip_get_line(chipEN,settings.EN_gpio);
        
        gpiod_line_request_output(pinEN,"Motor",0);  // open the pin to drive as output
        gpiod_line_set_value(pinEN,1); // sets EN pin to high 

        //CLASHES HERE WHEN RAN TWO TIMES IN A ROW
        // Initialise and autocallibrate
        i2c_writeByte(VIBRO_MODE_REG,DEVICE_RDY); // decide on whether we need both
        autoCal();
  
        i2c_writeByte(VIBRO_CONTROL1_REG,93);

        i2c_writeByte(VIBRO_CONTROL3_REG,80);

        i2c_writeByte(VIBRO_REGFIELD_REG,2);
        // put on standby for low pwer mode
        i2c_writeByte(VIBRO_MODE_REG,settings.standby); // also sets this to internal trigger

        #ifdef DEBUG
	fprintf(stderr,"Motor thread started.\n");
        #endif	
        running = 1;
        motorThread = std::thread(&VIBRO4_rpi::worker,this);

}

void VIBRO4_rpi::autoCal(){
        i2c_writeByte(VIBRO_CONTROL1_REG,motorSettings.init_control1_reg);

        i2c_writeByte(VIBRO_CONTROL3_REG,motorSettings.init_control3_reg);

        i2c_writeByte(VIBRO_CONTROL2_REG,motorSettings.init_control2_reg);

        i2c_writeByte(VIBRO_GO_REG,1);

        while (i2c_readByte(VIBRO_GO_REG)==1) {
                printf("Auto-calibration in progress.\n");
        }

        if (i2c_readByte(VIBRO_STATUS_REG)==DIAG_RESULT_FAIL){
                #ifdef DEBUG
                fprintf(stderr, "Auto-calibration failed.\n");
                #endif
                throw "Auto-calibration failed";
        };

        printf("Auto-calibration finished.\n");
        
}

void VIBRO4_rpi::vibroDiagnostic(){

        i2c_writeByte(VIBRO_MODE_REG,motorSettings.init_diagnostic_mode);
        i2c_writeByte(VIBRO_GO_REG,motorSettings.init_go);
        
        if (i2c_readByte(VIBRO_STATUS_REG)==DIAG_RESULT_FAIL){
                #ifdef DEBUG
                fprintf(stderr, "Actuator not working.\n");
                #endif
                throw "Actuator not working";
        };        
}


void VIBRO4_rpi::playHaptic_realTime(uint8_t amplitude){

        if(1 == running) {
                i2c_writeByte(VIBRO_MODE_REG,0);
                printf("Motor started \n");

                i2c_writeByte(VIBRO_MODE_REG,MODE_RTPLAYBACK);

                // Write amplitude for continuous vibration
                i2c_writeByte(VIBRO_RTP_REG,amplitude);


                i2c_writeByte(VIBRO_GO_REG,1);
        };

}

void VIBRO4_rpi::stopHaptic(){
        i2c_writeByte(VIBRO_RTP_REG,0);
        i2c_writeByte(VIBRO_MODE_REG,STANDBY);
}
 
void VIBRO4_rpi::stop(){
        if(!running) return;
        running = 0;
        changedState = false;
        motorThread.join();
        gpiod_line_set_value(pinEN,0);
        int status = i2c_readByte(VIBRO_MODE_REG);
        i2c_writeByte(VIBRO_MODE_REG,status|DEV_RESET);
        gpiod_line_release(pinEN);
 
        gpiod_chip_close(chipEN);
        #ifdef DEBUG
	fprintf(stderr,"Motor thread stopped.\n");
        #endif	


}

void VIBRO4_rpi::worker(){
        while (1 == running){
                char dataReady;
		read(*pfds_read, &dataReady, sizeof(char));
                if(changedState){
                        changedState = false;
                        if(activate){
                                playHaptic_realTime(vAmplitude);
                        }
                        else {
                                stopHaptic();
                        };
                };
        };
}
// i2c read and write protocols
void VIBRO4_rpi::i2c_writeByte(uint8_t reg, unsigned data)
{
        if (data > 0xFF) {
                #ifdef DEBUG
                fprintf(stderr,"Data %.2X is larger than 1 byte.\n",data);
                #endif
                throw "Data larger than 1 byte.";
        }
            
        char gpioFilename[20];
	snprintf(gpioFilename, 19, "/dev/i2c-%d", motorSettings.default_i2c_bus);
	fd_i2c = open(gpioFilename, O_RDWR);
	if (fd_i2c < 0) {
                char i2copen[] = "Could not open I2C.\n";
                #ifdef DEBUG
                fprintf(stderr,i2copen);
                #endif
                throw i2copen;
	}
	
	if (ioctl(fd_i2c, I2C_SLAVE, motorSettings.address) < 0) {
                char i2cslave[] = "Could not access I2C adress.\n";
                #ifdef DEBUG
                fprintf(stderr,i2cslave);
                #endif
                throw i2cslave;
        }
	
        uint8_t message[2];
        message[0] = reg & 0xFF; // MSB of register address
        message[1] = data & 0xFF; 
	long int r = write(fd_i2c, message ,2);
        if (r < 0) {
                #ifdef DEBUG
                fprintf(stderr,"Could not write byte to %02x. ret=%ld.\n",motorSettings.address,r);
                #endif
                throw "Could not write to i2c.";
        }

        close(fd_i2c);
}

unsigned VIBRO4_rpi::i2c_readByte(uint8_t reg){       
        char gpioFilename[20];
	snprintf(gpioFilename, 19, "/dev/i2c-%d", motorSettings.default_i2c_bus);
	fd_i2c = open(gpioFilename, O_RDWR);
	if (fd_i2c < 0) {
                char i2copen[] = "Could not open I2C.\n";
                #ifdef DEBUG
                fprintf(stderr,i2copen);
                #endif
                throw i2copen;
	}
	
	if (ioctl(fd_i2c, I2C_SLAVE, motorSettings.address) < 0) {
                char i2cslave[] = "Could not access I2C adress.\n";
                #ifdef DEBUG
                fprintf(stderr,i2cslave);
                #endif
                throw i2cslave;
	}

	uint8_t reg_address[1];
	reg_address[0] = reg;
	write(fd_i2c,reg_address,1);
        
        long int r;
        uint8_t data[1];
        r = read(fd_i2c,data,1);
        if (r<0){
                #ifdef DEBUG
                fprintf(stderr, "Could not read from %02x.\n",motorSettings.address);
                #endif
                throw "Could not read from sensor.";
        }
        close(fd_i2c);
        return ((uint8_t)(data[0]));
}