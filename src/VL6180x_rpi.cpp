#ifndef VL6180x_rpi
#include "VL6180x_rpi.h"
#endif
#include <bitset>
#include<unistd.h>

void VL6180x_rpi::startRangeContinuous(VL6180x_settings settings){
    if (running) return;

    sensorSettings = settings;

    //Initialise pigpio
    if(settings.initPIGPIO){
        int cfg = gpioCfgGetInternals();
        cfg |= PI_CFG_NOSIGHANDLER;
        gpioCfgSetInternals(cfg);
        int r = gpioInitialise();
        if (r < 0) {
            char msg[] = "Cannot init pigpio.";
            #ifdef DEBUG
            fprintf (stderr, "%s\n",msg);
            #endif
            throw msg;
        }
    }
    #ifdef DEBUG
    fprintf(stderr, "Init .\n");
    #endif

    //Hardware reset sensor using EN gpio pin
    // gpioSetMode(settings.en_gpio,PI_OUTPUT);
    // gpioWrite(settings.en_gpio,0);
    // gpioWrite(settings.en_gpio,1);
    // usleep(400);

    // //Wait for sensor to reboot
    // int FreshOutOfReset;
    // do {
    //     FreshOutOfReset = i2c_readByte(SENSOR_SYSTEM_FRESH_OUT_OF_RESET);
    // } while (FreshOutOfReset != 1);
    // fprintf(stderr,"Sensor rebooted successfully.\n");
    // i2c_writeByte(SENSOR_SYSTEM_FRESH_OUT_OF_RESET,0);

    //Write private registers from VL6180X API
    // i2c_writeByte(0x0207, 0x01);
    // i2c_writeByte(0x0208, 0x01);
    // i2c_writeByte(0x0096, 0x00);
    // i2c_writeByte(0x0097, 0xfd);
    // i2c_writeByte(0x00e3, 0x00);
    // i2c_writeByte(0x00e4, 0x04);
    // i2c_writeByte(0x00e5, 0x02);
    // i2c_writeByte(0x00e6, 0x01);
    // i2c_writeByte(0x00e7, 0x03);
    // i2c_writeByte(0x00f5, 0x02);
    // i2c_writeByte(0x00d9, 0x05);
    // i2c_writeByte(0x00db, 0xce);
    // i2c_writeByte(0x00dc, 0x03);
    // i2c_writeByte(0x00dd, 0xf8);
    // i2c_writeByte(0x009f, 0x00);
    // i2c_writeByte(0x00a3, 0x3c);
    // i2c_writeByte(0x00b7, 0x00);
    // i2c_writeByte(0x00bb, 0x3c);
    // i2c_writeByte(0x00b2, 0x09);
    // i2c_writeByte(0x00ca, 0x09);
    // i2c_writeByte(0x0198, 0x01);
    // i2c_writeByte(0x01b0, 0x17);
    // i2c_writeByte(0x01ad, 0x00);
    // i2c_writeByte(0x00ff, 0x05);
    // i2c_writeByte(0x0100, 0x05);
    // i2c_writeByte(0x0199, 0x05);
    // i2c_writeByte(0x01a6, 0x1b);
    // i2c_writeByte(0x01ac, 0x3e);
    // i2c_writeByte(0x01a7, 0x1f);
    // i2c_writeByte(0x0030, 0x00);

    fprintf(stderr,"P2P and CVH resets are %u and %u.\n",i2c_readByte(SENSOR_SYSRANGE_PART_TO_PART_RANGE_OFFSET),i2c_readByte(SENSOR_SYSRANGE_CROSSTALK_VALID_HEIGHT));
    i2c_writeByte(SENSOR_SYSRANGE_PART_TO_PART_RANGE_OFFSET,30);
    i2c_writeByte(SENSOR_SYSRANGE_CROSSTALK_VALID_HEIGHT,20);
    int scale = i2c_readTwoBytes(0x96);
    int p2p = i2c_readByte(SENSOR_SYSRANGE_PART_TO_PART_RANGE_OFFSET);
    int cvh = i2c_readByte(SENSOR_SYSRANGE_CROSSTALK_VALID_HEIGHT);
    fprintf(stderr,"New scalings are %u, %u and %u.\n",scale,p2p,cvh);

    //Write initial settings
    i2c_writeByte(SENSOR_SYSTEM_MODE_GPIO1,settings.system_mode_gpio1);
    i2c_writeByte(SENSOR_SYSTEM_INTERRUPT_CONFIG_GPIO,settings.system_interrupt_config_gpio);
    i2c_writeByte(SENSOR_SYSTEM_INTERRUPT_CLEAR,settings.system_interrupt_clear);
    i2c_writeByte(SENSOR_SYSRANGE_THRESH_LOW,settings.sysrange_thresh_low);
    i2c_writeByte(SENSOR_SYSRANGE_THRESH_HIGH,settings.sysrange_thresh_high);
    i2c_writeByte(SENSOR_SYSRANGE_INTERMEASUREMENT_PERIOD,settings.sysrange_intermeasurement_period);
    i2c_writeByte(SENSOR_SYSRANGE_MAX_CONVERGENCE_TIME,settings.sysrange_max_convergence_time);
    i2c_writeByte(SENSOR_SYSRANGE_RANGE_CHECK_ENABLES,settings.sysrange_range_check_enables);
    i2c_writeByte(SENSOR_SYSRANGE_START,settings.sysrange_start);
    gpioSetMode(settings.int_gpio,PI_INPUT);

    int mct = i2c_readByte(SENSOR_SYSRANGE_MAX_CONVERGENCE_TIME);
    fprintf(stderr,"Max Convergence Time is %u.\n",mct);

    #ifdef DEBUG
	fprintf(stderr,"Starting proximity thread.\n");
    #endif
    proxThread = std::thread(&VL6180x_rpi::run,this);

};

void VL6180x_rpi::run(){
    running = 1;
    #ifdef DEBUG
	fprintf(stderr,"Proximity thread running.\n");
    #endif
    gpioSetISRFuncEx(sensorSettings.int_gpio,RISING_EDGE,ISR_TIMEOUT,gpioISR,(void*)this);
};

void VL6180x_rpi::stop(){
    if (!running) return;
	running = 0;
    gpioSetISRFuncEx(sensorSettings.int_gpio,RISING_EDGE,-1,NULL,(void*)this);
    if(sensorSettings.initPIGPIO){
        gpioTerminate();
    }
    proxThread.join();
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

void VL6180x_rpi::dataReady(){
    int scale = i2c_readTwoBytes(0x96);
    int p2p = i2c_readByte(SENSOR_SYSRANGE_PART_TO_PART_RANGE_OFFSET);
    int cvh = i2c_readByte(SENSOR_SYSRANGE_CROSSTALK_VALID_HEIGHT);
    fprintf(stderr,"Scaling settings are %u, %u and %u.\n",scale,p2p,cvh);
    //need to assign an actual value
    uint8_t value = i2c_readByte(SENSOR_RESULT_RANGE_VAL);
    uint8_t error = i2c_readByte(SENSOR_RESULT_RANGE_STATUS);
    error = error >> 4;
    std::bitset<8> errorcode{error};
    #ifdef DEBUG
	fprintf(stderr,"Error code %u.\n",errorcode);
    #endif	
    sensorCallback->hasSample(value);
    #ifdef DEBUG
	fprintf(stderr,"Processed callback.\n");
    #endif
    //clear Range interupt
    i2c_writeByte(SENSOR_SYSTEM_INTERRUPT_CLEAR,(CLEAR_RANGE_INT|CLEAR_ALS_INT|CLEAR_ERROR_INT));
}

unsigned VL6180x_rpi::i2c_readTwoBytes(uint8_t reg)
{
    int fd = i2cOpen(sensorSettings.default_i2c_bus, sensorSettings.sensor_address, 0);
    if (fd<0){
        #ifdef DEBUG
        fprintf(stderr, "Could not open %02x.\n",sensorSettings.sensor_address);
        #endif
        throw could_not_open_i2c;
    }
    int r;
    char tmp[2];
    r = i2cReadI2CBlockData(fd,reg,tmp,2);
        if (r<0){
        #ifdef DEBUG
        fprintf(stderr, "Could not read from%02x.\n",sensorSettings.sensor_address,r);
        #endif
        throw "Could not read from i2c.";
    }
    i2cClose(fd);
    return (((unsigned)(tmp[0])) << 8) | ((unsigned)(tmp[1]));

};

unsigned VL6180x_rpi::i2c_readByte(uint8_t reg)
{
    //open sensor i2c comms
    int fd = i2cOpen(sensorSettings.default_i2c_bus, sensorSettings.sensor_address, 0);
    if (fd<0){
        #ifdef DEBUG
        fprintf(stderr, "Could not open %02x.\n",sensorSettings.sensor_address);
        #endif
        throw could_not_open_i2c;
    }
    //transmit a single read request to sensor for reg_address
    char reg_address[2];
    reg_address[0] = (reg >> 8) & 0xFF; // MSB of register address
    reg_address[1] = reg & 0xFF;        // LSB of register address
    i2cWriteDevice(fd,reg_address,2);
    //read one byte of data returned from the sensor
    int r;
    char data[1];
    r = i2cReadDevice(fd,data,1);
        if (r<0){
        #ifdef DEBUG
        fprintf(stderr, "Could not read from %02x.\n",sensorSettings.sensor_address);
        #endif
        throw "Could not read from sensor.";
    }
    i2cClose(fd);
    return ((unsigned)(data[0]));

};

//Can we call this writeTwoBytes instead of writeWord? It's confusing me...
void VL6180x_rpi::i2c_writeTwoBytes(uint8_t reg, unsigned data)
{
        int fd = i2cOpen(sensorSettings.default_i2c_bus, sensorSettings.sensor_address, 0);
        if (fd < 0) {
#ifdef DEBUG
                fprintf(stderr,"Could not open %02x.\n",sensorSettings.sensor_address);
#endif
                throw could_not_open_i2c;
        }
	char tmp[2];
	tmp[0] = (char)((data & 0xff00) >> 8);
	tmp[1] = (char)(data & 0x00ff);
	int r = i2cWriteI2CBlockData(fd, reg, tmp, 2);
        if (r < 0) {
#ifdef DEBUG
                fprintf(stderr,"Could not write two bytes to %02x. ret=%d.\n",sensorSettings.sensor_address,r);
#endif
                throw "Could not write to i2c.";
        }
        i2cClose(fd);
}

void VL6180x_rpi::i2c_writeByte(uint8_t reg, unsigned data)
{
        int fd = i2cOpen(sensorSettings.default_i2c_bus, sensorSettings.sensor_address, 0);
        if (fd < 0) {
        #ifdef DEBUG
                fprintf(stderr,"Could not open %02x.\n",sensorSettings.sensor_address);
        #endif
                throw could_not_open_i2c;
        }
	
        if (data > 0xFF) {
        #ifdef DEBUG
                fprintf(stderr,"Data %.2X is larger than 1 byte.\n",data);
        #endif
                throw "Data larger than 1 byte.";
        }
    // Cast data to char = 1 byte = 8 bits
    char message[3];
    message[0] = (reg >> 8) & 0xFF; // MSB of register address
    message[1] = reg & 0xFF;        // LSB of register address
    message[2] = data & 0xFF;

	int r = i2cWriteDevice(fd, message, 3);
        if (r < 0) {
#ifdef DEBUG
                fprintf(stderr,"Could not write byte to %02x. ret=%d.\n",sensorSettings.sensor_address,r);
#endif
                throw "Could not write to i2c.";
        }
        i2cClose(fd);
}