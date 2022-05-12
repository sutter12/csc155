#include<stdio.h>
#include<regex.h>
#include<fcntl.h>
#include<unistd.h>
#include<bcm2835.h>

#ifndef I2C

#define I2C

int i2cInit(unsigned char address);

int write8(unsigned char reg, unsigned char value);

unsigned char readU8(unsigned char reg);

#endif
