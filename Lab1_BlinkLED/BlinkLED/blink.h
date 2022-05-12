//Author: Alexander Sutter

#include <bcm2835.h>
#include <stdio.h>

//function prototyping
void ledBlink(int pin, int duration);
void ledAlternate(int pin1, int pin2, int duration);
void ledPolice(int pin1, int pin2);