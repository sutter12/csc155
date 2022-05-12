#include <stdio.h>
#include <bcm2835.h>
#include "MotorHat.h"
#include "PWM.h"

int PWMpin;
int IN1pin;
int IN2pin;
unsigned char _i2caddr;
int _frequency;

void initMotors() {
    // self.MC = controller
    // self.motornum = num
    // motor.pwm = 0;
    // motor.in1 = 0;
    // motor.in2 = 0;

    //motors 0
    motors[0].pwm = 8;
    motors[0].in2 = 9;
    motors[0].in1 = 10;
    
    //motors 1
    motors[1].pwm = 13;
    motors[1].in2 = 12;
    motors[1].in1 = 11;
    
    //motors 2
    motors[2].pwm = 2;
    motors[2].in2 = 3;
    motors[2].in1 = 4;
    
    //motors 3
    motors[3].pwm = 7;
    motors[3].in2 = 6;
    motors[3].in1 = 5;
    
    // PWMpin = motor.pwm;
    // IN1pin = motor.in1;
    // IN2pin = motor.in2;
}//end initMotors

void initHat(unsigned char address, int freq) {
    _i2caddr = address;           // default addr on HAT
    _frequency = freq;        // default @1600Hz PWM freq
    // motors = [ Adafruit_DCMotor(self, m) for m in range(4) ];
    // steppers = [ Adafruit_StepperMotor(self, 1), Adafruit_StepperMotor(self, 2) ];
    PWMInit(address);
    initMotors();
    setPWMFreq(_frequency);
}//end initHat

void run(unsigned char command, unsigned char motorID) {
    if (command == FORWARD){
        setPin(motors[motorID].in2, 0);
        setPin(motors[motorID].in1, 1);
    }//end if statement
        
    if (command == BACKWARD){
        setPin(motors[motorID].in1, 0);
        setPin(motors[motorID].in2, 1);
    }//end if statement
        
    if (command == RELEASE){
        setPin(motors[motorID].in2, 0);
        setPin(motors[motorID].in1, 0);
    }//end if statement
}//end run

void setPin(unsigned char pin, unsigned char value) {
    if ((pin < 0) || (pin > 15)) {
        printf("PWM pin must be between 0 and 15 inclusive");
    }//end if statement
    if ((value != 0) && (value != 1)) {
        printf("Pin value must be 0 or 1!");
    }//end if statement
    if (value == 0) {
        setPWM(pin, 0, 4096);
    }//end if statement
    if (value == 1) {
        setPWM(pin, 4096, 0);
    }//end if statement
}//end setPin

motor getMotor(int num) {
    if ((num < 1) || (num > 4)) {
        printf("MotorHAT Motor must be between 1 and 4 inclusive");
    }//end if statement
    return motors[num];
}//end getMotor

void setSpeed(int speed, unsigned char motorID) {
    if (speed < 0) {
        speed = 0;
    }//end if statement
    if (speed > 255) {
        speed = 255;
    }//end if statement
    printf("speed - %d", speed);
    printf("speed*16 - %d", speed*16);
    setPWM(motors[motorID].pwm, 0, speed*16);
}//end setSpeed