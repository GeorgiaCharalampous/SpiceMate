#ifndef VL6180x_rpi
#include "VL6180x_rpi.h"
#endif


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
    //need to assign an actual value
    uint8_t value = i2cReadByte(SENSOR_RESULT_RANGE_VAL);
    #ifdef DEBUG
	fprintf(stderr,"Data acquired %u.\n",value);
    #endif	
    sensorCallback->hasSample(value);
    #ifdef DEBUG
	fprintf(stderr,"Processed callback.\n");
    #endif
    //clear Range interupt
    i2c_writeByte(SENSOR_SYSTEM_INTERRUPT_CLEAR,CLEAR_RANGE_INT);
}

unsigned VL6180x_rpi::i2c_readTwoBytes(uint8_t reg)
{
    int fd = i2cOpen(sensorSettings.default_i2c_bus, sensorSettings.address, 0);
    if (fd<0){
        #ifdef DEBUG
        fprintf(stderr, "Could not open %02x.\n",sensorSettings.address);
        #endif
        throw could_not_open_i2c;
    }
    int r;
    char tmp[2];
    r = i2cReadI2CBlockData(fd,reg,tmp,2);
        if (r<0){
        #ifdef DEBUG
        fprintf(stderr, "Could not read from%02x.\n",sensorSettings.address,r);
        #endif
        throw "Could not read from i2c.";
    }
    i2cClose(fd);
    return (((unsigned)(tmp[0])) << 8) | ((unsigned)(tmp[1]));

};

unsigned VL6180x_rpi::i2c_readByte(uint8_t reg)
{
    int fd = i2cOpen(sensorSettings.default_i2c_bus, sensorSettings.address, 0);
    if (fd<0){
        #ifdef DEBUG
        fprintf(stderr, "Could not open %02x.\n",sensorSettings.address);
        #endif
        throw could_not_open_i2c;
    }
    int r;
    char tmp[1];
    r = i2cReadI2CBlockData(fd,reg,tmp,1);
        if (r<0){
        #ifdef DEBUG
        fprintf(stderr, "Could not read from%02x.\n",sensorSettings.address,r);
        #endif
        throw "Could not read from i2c.";
    }
    i2cClose(fd);
    return ((unsigned)(tmp[0]));

};

//Can we call this writeTwoBytes instead of writeWord? It's confusing me...
void VL6180x_rpi::i2c_writeTwoBytes(uint8_t reg, unsigned data)
{
        int fd = i2cOpen(sensorSettings.default_i2c_bus, sensorSettings.address, 0);
        if (fd < 0) {
#ifdef DEBUG
                fprintf(stderr,"Could not open %02x.\n",sensorSettings.address);
#endif
                throw could_not_open_i2c;
        }
	char tmp[2];
	tmp[0] = (char)((data & 0xff00) >> 8);
	tmp[1] = (char)(data & 0x00ff);
	int r = i2cWriteI2CBlockData(fd, reg, tmp, 2);
        if (r < 0) {
#ifdef DEBUG
                fprintf(stderr,"Could not write two bytes to %02x. ret=%d.\n",sensorSettings.address,r);
#endif
                throw "Could not write to i2c.";
        }
        i2cClose(fd);
}

void VL6180x_rpi::i2c_writeByte(uint8_t reg, unsigned data)
{
        int fd = i2cOpen(sensorSettings.default_i2c_bus, sensorSettings.address, 0);
        if (fd < 0) {
#ifdef DEBUG
                fprintf(stderr,"Could not open %02x.\n",sensorSettings.address);
#endif
                throw could_not_open_i2c;
        }
	// Cast data to char = 1 byte = 8 bits
	
        if (data > 0xFF) {
#ifdef DEBUG
                fprintf(stderr,"Data %.2X is larger than 1 byte.\n",data);
#endif
                throw "Data larger than 1 byte.";
        }
    char tmp[1];
    tmp[0] = (char)(data);

	int r = i2cWriteI2CBlockData(fd, reg, tmp, 1);
        if (r < 0) {
#ifdef DEBUG
                fprintf(stderr,"Could not write byte to %02x. ret=%d.\n",sensorSettings.address,r);
#endif
                throw "Could not write to i2c.";
        }
        i2cClose(fd);
}