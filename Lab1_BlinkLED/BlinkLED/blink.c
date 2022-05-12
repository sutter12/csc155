//Author: Alexander Sutter
#include <bcm2835.h>
#include "blink.h"

// Blinks on RPi Plug P1 pin 11 (which is GPIO pin 17)
#define PIN RPI_GPIO_P1_11
// Blinks on RPi Plug P1 pin 13 (which is GPIO pin 27)
#define PIN2 RPI_GPIO_P1_15

//functions
// ledBlink() - blinks led at pin on for a duration then off
void ledBlink(int pin, int duration) {
  // Turn on
  bcm2835_gpio_write(pin, HIGH);
  
  // wait a bit
  bcm2835_delay(duration);
  
  // turn off
  bcm2835_gpio_write(pin, LOW);
  
  // wait a bit
  bcm2835_delay(duration);
}//end ledBlink

void ledAlternate(int pin1, int pin2, int duration) {
  while(1) {
    ledBlink(pin1, 500);
    ledBlink(pin2, 500);
  }//end while loop
}//end ledAlternate

void ledPolice(int pin1, int pin2) {
  int wait = 100;
  while(1) {
    for(int x=0; x<3; x++) {
      ledBlink(pin1, wait);
    }//end for x loop
    for(int y=0; y<3; y++) {
      ledBlink(pin2, wait);
    }//end for y loop
  }//end while loop
}//end ledPolice
