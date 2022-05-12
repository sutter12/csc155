#include <stdio.h>
#include <stdlib.h>
#include <bcm2835.h>
#include "MotorHat.h"

#ifndef ROBOT
#define ROBOT

void init(unsigned char addr, int left_id, int right_id, int left_trim, int right_trim, int stop_at_exit);

int max(int num1, int num2);
int min(int num1, int num2);

void _left_speed(int speed);
void _right_speed(int speed);
void stop();

void forward(int speed, float time);
void backward(int speed, float time);
void right(int speed, float time);
void left(int speed, float time);

#endif

