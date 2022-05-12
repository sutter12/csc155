#include<stdio.h>
#include<regex.h>
#include<fcntl.h>
#include<unistd.h>
#include<bcm2835.h>
#include "I2C.h"


extern int i2cInit(unsigned char address){
	
	
	//i2c initialization should also go here.
	
	if (!bcm2835_init())
    	{
     		printf("bcm2835_init failed. Are you running as root??\n");
      		return 1;
    	}//if bcm_init
	
	if (!bcm2835_i2c_begin())
    	{
		printf("bcm2835_i2c_begin failed. Are you running as root??\n");
		return 1;
	}//if i2c_begin

	bcm2835_i2c_setSlaveAddress(address); 
	return 0;
	
	
}

extern  int  write8(unsigned char reg, unsigned char value){
	char buff[2];
	buff[0] = reg;
	buff[1] = value;
	
	if (bcm2835_i2c_write(buff, 2)== BCM2835_I2C_REASON_OK){
		//printf("Success!!!!!!!\n");
	}else{
		printf("Failure!!!!!!!\n");
	}

	return 0;
}

extern unsigned char readU8(unsigned char reg){
	unsigned char data;
	char buff[2];
	buff[0] = reg;
	
	if(bcm2835_i2c_read(buff,2) == BCM2835_I2C_REASON_OK){
		//printf("Success with ReadU8!!!!!\n");
	}else{
		printf("Failure with ReadU8!!!!!\n");
	}
	return buff[0];
}


