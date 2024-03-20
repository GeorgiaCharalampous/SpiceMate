#include "VL6180x_rpi.h"

void VL6180x_rpi::startRangeContinuous(VL6180x_settings settings){
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

    //Enable interrups
    i2c_writeTwoBytes(reg_lo_thres,0x0000);
    i2c_writeTwoBytes(reg_hi_thres,0x8000);

    gpioSetISRFuncEx(sensorSettings.int_gpio,RISING_EDGE,ISR_TIMEOUT,gpioISR,(void*)this);

};

void VL6180x_rpi::stop(){
    gpioSetISRFuncEx(sensorSettings.int_gpio,RISING_EDGE,-1,NULL,(void*)this);
    if(sensorSettings.initPIGPIO){
        gpioTerminate();
    }
};

void VL6180x_rpi::registerCallback(VL6180xcallback* cb){
    sensorCallback = cb;
};

void VL6180x_rpi::unRegisterCallback(){
    sensorCallback = nullptr;
};

void VL6180x_rpi::dataReady(){
    //need to assign an actual value
    uint8_t value;
    sensorCallback->hasSample(value);
}

unsigned VL6180x_rpi::i2c_readWord(uint8_t reg)
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