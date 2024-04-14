#ifndef VL6180x_rpi
#include "VL6180x_rpi.h"
#endif
#include <bitset>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ioctl.h>


void VL6180x_rpi::startRangeContinuous(VL6180x_settings settings){
    if (running) return;

    sensorSettings = settings;

    chipEN = gpiod_chip_open_by_number(settings.en_chip);
    pinEN = gpiod_chip_get_line(chipEN,settings.en_gpio);
    gpiod_line_request_output(pinEN,"Consumer",0);
    gpiod_line_set_value(pinEN,1);
    usleep(400);

    //Wait for sensor to reboot
    int FreshOutOfReset;
    do {
        FreshOutOfReset = i2c_readByte(SENSOR_SYSTEM_FRESH_OUT_OF_RESET);
        fprintf(stderr,"I am waiting for reboot.\n");
    } while (FreshOutOfReset != 1);
    fprintf(stderr,"Sensor rebooted successfully.\n");
    i2c_writeByte(SENSOR_SYSTEM_FRESH_OUT_OF_RESET,0);

    fprintf(stderr,"Default Scale, P2P and CVH are %u, %u and %u. \n",i2c_readTwoBytes(0x96), i2c_readByte(SENSOR_SYSRANGE_PART_TO_PART_RANGE_OFFSET),i2c_readByte(SENSOR_SYSRANGE_CROSSTALK_VALID_HEIGHT));
    i2c_writeTwoBytes(0x96,127);
    unsigned scale = i2c_readTwoBytes(0x96);

    unsigned p2p = i2c_readByte(SENSOR_SYSRANGE_PART_TO_PART_RANGE_OFFSET);
    i2c_writeByte(SENSOR_SYSRANGE_PART_TO_PART_RANGE_OFFSET,p2p/2);
    p2p = i2c_readByte(SENSOR_SYSRANGE_PART_TO_PART_RANGE_OFFSET);

    i2c_writeByte(SENSOR_SYSRANGE_CROSSTALK_VALID_HEIGHT,20/2);
    unsigned cvh = i2c_readByte(SENSOR_SYSRANGE_CROSSTALK_VALID_HEIGHT);
    fprintf(stderr,"New scalings are %u, %u and %u.\n",scale,p2p,cvh);

    unsigned rce = i2c_readByte(SENSOR_SYSRANGE_RANGE_CHECK_ENABLES);
    i2c_writeByte(SENSOR_SYSRANGE_RANGE_CHECK_ENABLES, (rce & 0xFE) | (false));

    //Write initial settings
    i2c_writeByte(SENSOR_SYSTEM_MODE_GPIO1,settings.system_mode_gpio1);
    i2c_writeByte(SENSOR_SYSTEM_INTERRUPT_CONFIG_GPIO,settings.system_interrupt_config_gpio);
    i2c_writeByte(SENSOR_SYSTEM_INTERRUPT_CLEAR,settings.system_interrupt_clear);
    i2c_writeByte(SENSOR_SYSRANGE_THRESH_LOW,settings.sysrange_thresh_low);
    i2c_writeByte(SENSOR_SYSRANGE_THRESH_HIGH,settings.sysrange_thresh_high);
    i2c_writeByte(SENSOR_SYSRANGE_INTERMEASUREMENT_PERIOD,settings.sysrange_intermeasurement_period);
    i2c_writeByte(SENSOR_SYSRANGE_MAX_CONVERGENCE_TIME,settings.sysrange_max_convergence_time);
    //i2c_writeByte(SENSOR_SYSRANGE_RANGE_CHECK_ENABLES,settings.sysrange_range_check_enables);
    i2c_writeByte(SENSOR_SYSRANGE_START,settings.sysrange_start);

    int mct = i2c_readByte(SENSOR_SYSRANGE_MAX_CONVERGENCE_TIME);
    fprintf(stderr,"Max Convergence Time is %u.\n",mct);


    chipINT = gpiod_chip_open_by_number(settings.int_chip);
    pinINT = gpiod_chip_get_line(chipINT,settings.int_gpio);

    int ret = gpiod_line_request_rising_edge_events(pinINT, "Apple");
        if (ret < 0) {
    #ifdef DEBUG
            fprintf(stderr,"Request event notification failed on pin %d and chip %d.\n",settings.int_chip,settings.int_gpio);
    #endif
            throw "Could not request event for IRQ.";
        }


    #ifdef DEBUG
	fprintf(stderr,"Starting proximity thread.\n");
    #endif
    running = 1;
    proxThread = std::thread(&VL6180x_rpi::worker,this);

};


void VL6180x_rpi::stop(){
    if (!running) return;
	running = 0;
    proxThread.join();
    gpiod_line_release(pinINT);
    gpiod_chip_close(chipINT);
    gpiod_line_release(pinEN);
    gpiod_chip_close(chipEN);
    #ifdef DEBUG
	fprintf(stderr,"Proximity thread stopped.\n");
    #endif	
};

void VL6180x_rpi::registerCallback(VL6180xcallback* cb){
    sensorCallback = cb;
};

void VL6180x_rpi::unRegisterCallback(){
    sensorCallback = nullptr;
};

void VL6180x_rpi::worker(){
    while (1 == running) {
        const struct timespec ts = { 1, 0 };
        gpiod_line_event_wait(pinINT, &ts);
        struct gpiod_line_event event;
        gpiod_line_event_read(pinINT, &event);
        dataReady();
    }
}

/* DEBUG ONLY; REMOVE FROM FINAL VERSION
void VL6180x_rpi::getStatus(){
    int a = i2c_readByte(SENSOR_RESULT_INTERRUPT_STATUS_GPIO);
    int error = i2c_readByte(SENSOR_RESULT_RANGE_STATUS);
    error = error >> 4;
    printf("Error code is %u. \n",error);
    printf("Current Interupt status is %u. \n",a);
    printf("Sensor Start status is %u. \n",i2c_readByte(SENSOR_SYSRANGE_START));
    //printf("Interleave status is %u. \n",i2c_readByte(0x2A3));
    sleep(1);
}
*/

void VL6180x_rpi::dataReady(){
    unsigned scale = i2c_readTwoBytes(0x96);
    int p2p = i2c_readByte(SENSOR_SYSRANGE_PART_TO_PART_RANGE_OFFSET);
    int cvh = i2c_readByte(SENSOR_SYSRANGE_CROSSTALK_VALID_HEIGHT);
    //need to assign an actual value
    uint8_t value = i2c_readByte(SENSOR_RESULT_RANGE_VAL);
    int error = i2c_readByte(SENSOR_RESULT_RANGE_STATUS);
    error = error >> 4;
    #ifdef DEBUG
	//fprintf(stderr,"Error code %u.\n",error);
    #endif	
    sensorCallback->hasSample(value);
    //clear All interupts
    i2c_writeByte(SENSOR_SYSTEM_INTERRUPT_CLEAR,(CLEAR_RANGE_INT|CLEAR_ALS_INT|CLEAR_ERROR_INT));
    #ifdef DEBUG
	//fprintf(stderr,"Processed callback.\n");
    #endif
    i2c_writeByte(SENSOR_SYSRANGE_START,3);
    i2c_writeByte(SENSOR_SYSRANGE_START,3);

}

unsigned VL6180x_rpi::i2c_readTwoBytes(uint8_t reg)
{
    char gpioFilename[20];
	snprintf(gpioFilename, 19, "/dev/i2c-%d", sensorSettings.default_i2c_bus);
	fd_i2c = open(gpioFilename, O_RDWR);
	if (fd_i2c < 0) {
	    char i2copen[] = "Could not open I2C.\n";
    #ifdef DEBUG
	    fprintf(stderr,i2copen);
    #endif
	    throw i2copen;
	}
	
	if (ioctl(fd_i2c, I2C_SLAVE, sensorSettings.sensor_address) < 0) {
	    char i2cslave[] = "Could not access I2C adress.\n";
    #ifdef DEBUG
	    fprintf(stderr,i2cslave);
    #endif
	    throw i2cslave;
	}



    //transmit a single read request to sensor for reg_address
    uint8_t reg_address[2];
    reg_address[0] = (reg >> 8) & 0xFF; // MSB of register address
    reg_address[1] = reg & 0xFF;        // LSB of register address
    write(fd_i2c,reg_address,2);

    //read one byte of data returned from the sensor
    long int r;
    uint8_t data[2];
    r = read(fd_i2c,data,2);
        if (r<0){
        #ifdef DEBUG
        fprintf(stderr, "Could not read from %02x.\n",sensorSettings.sensor_address);
        #endif
        throw "Could not read from sensor.";
    }
    close(fd_i2c);
    return ((((unsigned)(data[0])) << 8) | ((unsigned)(data[1])));
};

unsigned VL6180x_rpi::i2c_readByte(uint8_t reg)
{
    char gpioFilename[20];
	snprintf(gpioFilename, 19, "/dev/i2c-%d", sensorSettings.default_i2c_bus);
	fd_i2c = open(gpioFilename, O_RDWR);
	if (fd_i2c < 0) {
	    char i2copen[] = "Could not open I2C.\n";
    #ifdef DEBUG
	    fprintf(stderr,i2copen);
    #endif
	    throw i2copen;
	}
	
	if (ioctl(fd_i2c, I2C_SLAVE, sensorSettings.sensor_address) < 0) {
	    char i2cslave[] = "Could not access I2C adress.\n";
    #ifdef DEBUG
	    fprintf(stderr,i2cslave);
    #endif
	    throw i2cslave;
	}
    //transmit a single read request to sensor for reg_address
    uint8_t reg_address[2];
    reg_address[0] = (reg >> 8) & 0xFF; // MSB of register address
    reg_address[1] = reg & 0xFF;        // LSB of register address
    write(fd_i2c,reg_address,2);
    //read one byte of data returned from the sensor
    long int r;
    uint8_t data[1];
    r = read(fd_i2c,data,1);
    if (r<0){
        #ifdef DEBUG
        fprintf(stderr, "Could not read from %02x.\n",sensorSettings.sensor_address);
        #endif
        throw "Could not read from sensor.";
    }
    close(fd_i2c);
    return ((uint8_t)(data[0]));

};

void VL6180x_rpi::i2c_writeTwoBytes(uint8_t reg, unsigned data)
{
    char gpioFilename[20];
	snprintf(gpioFilename, 19, "/dev/i2c-%d", sensorSettings.default_i2c_bus);
	fd_i2c = open(gpioFilename, O_RDWR);
	if (fd_i2c < 0) {
	    char i2copen[] = "Could not open I2C.\n";
    #ifdef DEBUG
	    fprintf(stderr,i2copen);
    #endif
	    throw i2copen;
	}
	
	if (ioctl(fd_i2c, I2C_SLAVE, sensorSettings.sensor_address) < 0) {
	    char i2cslave[] = "Could not access I2C adress.\n";
    #ifdef DEBUG
	    fprintf(stderr,i2cslave);
    #endif
	    throw i2cslave;
    }

    uint8_t message[4];
    message[0] = (reg >> 8) & 0xFF; // MSB of register address
    message[1] = reg & 0xFF;        // LSB of register address
    message[2] = (data >> 8) & 0xFF;// MSB of data to be written
    message[3] = data & 0xFF;       // LSB of data to be written

    long int r = write(fd_i2c, message, 4);
    if (r < 0) {
    #ifdef DEBUG
        fprintf(stderr,"Could not write byte to %02x. ret=%ld.\n",sensorSettings.sensor_address,r);
    #endif
        throw "Could not write to i2c.";
    }
    
    close(fd_i2c);
}

void VL6180x_rpi::i2c_writeByte(uint8_t reg, unsigned data)
{
    if (data > 0xFF) {
    #ifdef DEBUG
            fprintf(stderr,"Data %.2X is larger than 1 byte.\n",data);
    #endif
            throw "Data larger than 1 byte.";
    }

    char gpioFilename[20];
	snprintf(gpioFilename, 19, "/dev/i2c-%d", sensorSettings.default_i2c_bus);
	fd_i2c = open(gpioFilename, O_RDWR);
	if (fd_i2c < 0) {
	    char i2copen[] = "Could not open I2C.\n";
    #ifdef DEBUG
	    fprintf(stderr,i2copen);
    #endif
	    throw i2copen;
	}
	
	if (ioctl(fd_i2c, I2C_SLAVE, sensorSettings.sensor_address) < 0) {
	    char i2cslave[] = "Could not access I2C adress.\n";
    #ifdef DEBUG
	    fprintf(stderr,i2cslave);
    #endif
	    throw i2cslave;
    }

    uint8_t message[3];
    message[0] = (reg >> 8) & 0xFF; // MSB of register address
    message[1] = reg & 0xFF;        // LSB of register address
    message[2] = data & 0xFF;       // Data to be written

    long int r = write(fd_i2c, message, 3);
    if (r < 0) {
    #ifdef DEBUG
        fprintf(stderr,"Could not write byte to %02x. ret=%ld.\n",sensorSettings.sensor_address,r);
    #endif
        throw "Could not write to i2c.";
    }
    
    close(fd_i2c);
}