#include <stdio.h>
#include <stdlib.h>
#include <bcm2835.h>
#include "MotorHat.h"
#include "Robot.h"

int _left_trim;
int _right_trim;
// motor _right;
// motor _left;

int _left = 0;
int _right = 1;

void init(unsigned char addr, int left_id, int right_id, int left_trim, int right_trim, int stop_at_exit) {
    // """Create an instance of the robot.  Can specify the following optional
    // parameters:
    //     - addr: The I2C address of the motor HAT, default is 0x60.
    //     - left_id: The ID of the left motor, default is 1.
    //     - right_id: The ID of the right motor, default is 2.
    //     - left_trim: Amount to offset the speed of the left motor, can be positive
    //                 or negative and use useful for matching the speed of both
    //                 motors.  Default is 0.
    //     - right_trim: Amount to offset the speed of the right motor (see above).
    //     - stop_at_exit: Boolean to indicate if the motors should stop on program
    //                     exit.  Default is True (highly recommended to keep this
    //                     value to prevent damage to the bot on program crash!).
    // """
    // # Initialize motor HAT and left, right motor.
    initHat(addr, 1600);
    // _left = getMotor(left_id);
    // _right = getMotor(right_id);
    _left_trim = left_trim;
    _right_trim = right_trim;
    // # Start with motors turned off.
    run(RELEASE, _left);
    run(RELEASE, _right);
    // // Configure all motors to stop at program exit if desired.
    if (stop_at_exit == 1) {
        atexit(stop);
    }//end if statement
}//end init

int max(int num1, int num2) {
    return(num1 > num2) ? num1:num2;
}

int min(int num1, int num2) {
    return(num1 > num2) ? num2:num1;
}

void _left_speed(int speed) {
    // """Set the speed of the left motor, taking into account its trim offset.
    if (0 <= speed && speed <= 255) {
        speed += _left_trim;
        int mini = min(255, speed);
        speed = max(0, mini);  // Constrain speed to 0-255 after trimming.
        setSpeed(speed, _left);
    }//end if statement
    else {
        printf("Speed must be a value between 0 to 255 inclusive!");
    }//end else statement
}//end _left_speed

void _right_speed(int speed) {
    // """Set the speed of the right motor, taking into account its trim offset.
    if (0 <= speed && speed <= 255) {
        speed += _right_trim;
        speed = max(0, min(255, speed));  // Constrain speed to 0-255 after trimming.
        setSpeed(speed, _right);
    }//end if statement
    else {
        printf("Speed must be a value between 0 to 255 inclusive!");
    }//end else statement
}//end _right_speed

void stop() {
    // """Stop all movement."""
    run(RELEASE, _left);//left
    run(RELEASE, _right);//right
}//end stop

void forward(int speed, float time) {
    // """Move forward at the specified speed (0-255).  Will start moving
    // forward and return unless a seconds value is specified, in which
    // case the robot will move forward for that amount of time and then stop.
    // """
    // Set motor speed and move both forward.
    _left_speed(speed);
    _right_speed(speed);
    run(FORWARD, _left);
    run(FORWARD, _right);
    // If an amount of time is specified, move for that time and then stop.
    time = time * 1000;
    if (time > 0) {
        bcm2835_delay(time);
        stop();
    }//end if statement
}//end forward

void backward(int speed, float time) {
    // """Move backward at the specified speed (0-255).  Will start moving
    // backward and return unless a seconds value is specified, in which
    // case the robot will move backward for that amount of time and then stop.
    // """
    // Set motor speed and move both backward.
    _left_speed(speed);
    _right_speed(speed);
    run(BACKWARD, _left);
    run(BACKWARD, _right);
    // If an amount of time is specified, move for that time and then stop.
    time = time * 1000;
    if (time > 0)  {
        bcm2835_delay(time);
        stop();
    }//end if statement
}//end backwards

void right(int speed, float time) {
    // """Spin to the right at the specified speed.  Will start spinning and
    // return unless a seconds value is specified, in which case the robot will
    // spin for that amount of time and then stop.
    // """
    // Set motor speed and move both forward.
    _left_speed(speed);
    _right_speed(speed);
    run(FORWARD, _left);
    run(BACKWARD, _right);
    // If an amount of time is specified, move for that time and then stop.
    time = time * 1000;
    if (time > 0) {
        bcm2835_delay(time);
        stop();
    }//end if statement
}//end right

void left(int speed, float time) {
    // """Spin to the left at the specified speed.  Will start spinning and
    // return unless a seconds value is specified, in which case the robot will
    // spin for that amount of time and then stop.
    // """
    // Set motor speed and move both forward.
    _left_speed(speed);
    _right_speed(speed);
    run(BACKWARD, _left);
    run(FORWARD, _right);
    // If an amount of time is specified, move for that time and then stop.
    time = time * 1000;
    if (time > 0) {
        bcm2835_delay(time);
        stop();
    }//end if statement
}//end left