#include <stdio.h>
#include <regex.h>
#include <fcntl.h>
#include <unistd.h>
#include <bcm2835.h>
#include <math.h>
#include "PWM.h"
#include "I2C.h"

int _I2C;
unsigned int Address;
unsigned int mode1;
float prescaleval;
double prescale;
unsigned char oldmode;
unsigned char newmode;

void setAllPWM(int on, int off) {
    //"Sets a all PWM channels"
    write8(__ALL_LED_ON_L, on & 0xFF);
    write8(__ALL_LED_ON_H, on >> 8);
    write8(__ALL_LED_OFF_L, off & 0xFF);
    write8(__ALL_LED_OFF_H, off >> 8);
}//end setAllPWM

void PWMInit(unsigned int address) {
    _I2C = i2cInit(address);
    Address = address;
    // self.i2c = Adafruit_I2C(address)
    // self.i2c.debug = debug
    // self.address = address
    // self.debug = debug
    // if (self.debug):
    //   print "Reseting PCA9685 MODE1 (without SLEEP) and MODE2"
    setAllPWM(0, 0);
    write8(__MODE2, __OUTDRV);
    write8(__MODE1, __ALLCALL);
    bcm2835_delay(5);
    // time.sleep(0.005)

    mode1 = readU8(__MODE1);
    mode1 = mode1 & ~ __SLEEP;
    write8(__MODE1, mode1);
    bcm2835_delay(5);
    // time.sleep(0.005)
}//end PWMInit

void setPWMFreq(int freq) {
    //"Sets the PWM frequency"
    prescaleval = 25000000.0; //25MHz
    printf("prescaleval = %f\n", prescaleval);
    prescaleval /= 4096.0; //12-bit
    printf("prescaleval = %f\n", prescaleval);
    prescaleval /= (float)freq;
    printf("prescaleval = %f\n", prescaleval);
    prescaleval -= 1.0;
    printf("prescaleval = %f\n", prescaleval);
    // if (self.debug):
    //   print "Setting PWM frequency to %d Hz" % freq
    //   print "Estimated pre-scale: %d" % prescaleval
    double temp = (double)prescaleval + 0.5;
    printf("temp = %f\n", temp);
    prescale = floor(temp);
    printf("prescale = %f\n", prescale);
    // if (self.debug):
    //   print "Final pre-scale: %d" % prescale
    //
    oldmode = readU8(__MODE1);
    printf("oldmode = %d\n", oldmode);
    newmode = (oldmode & 0x7F) | 0x10;
    printf("newmode = %d\n", newmode);
    write8(__MODE1, newmode);
    write8(__PRESCALE, (int)(floor(prescale)));
    write8(__MODE1, oldmode);
    bcm2835_delay(500);
    // time.sleep(0.005)
    write8(__MODE1, oldmode | 0x80);
}//end setPWMFreq

void setPWM(int channel, unsigned int on, unsigned int off) {
    printf("channel - %d, on - %d, off - %d", channel, on, off);
    //"Sets a single PWM channel"
    write8(__LED0_ON_L+4*channel, on & 0xFF);
    write8(__LED0_ON_H+4*channel, on >> 8);
    write8(__LED0_OFF_L+4*channel, off & 0xFF);
    write8(__LED0_OFF_H+4*channel, off >> 8);
}//end setPWM