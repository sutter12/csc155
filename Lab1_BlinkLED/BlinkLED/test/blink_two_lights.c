// blink.c
/*
Example program for bcm2835 library
Blinks a pin on an off every 0.5 secs

After installing bcm2835, you can build this 
with something like:
gcc -o blink blink.c -l bcm2835
sudo ./blink

Author: Alexander Sutter
Copyright (C) 2021 Alexander Sutter
*/

#include <bcm2835.h>
#include <stdio.h>

// Blinks on RPi Plug P1 pin 11 (which is GPIO pin 17)
#define PIN RPI_GPIO_P1_11
// Blinks on RPi Plug P1 pin 13 (which is GPIO pin 27)
#define PIN2 RPI_GPIO_P1_15

//function prototyping
void ledBlink(int pin, int duration);
void ledAlternate(int pin1, int pin2, int duration);
void ledPolice(int pin1, int pin2);

int main(int argc, char **argv) {
  // If you call this, it will not actually access the GPIO
  // Use for testing
  // bcm2835_set_debug(1);
  if (!bcm2835_init()) {
    return 1;
  }//if statement
  // Set the pins to be an output
  bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(PIN2, BCM2835_GPIO_FSEL_OUTP);
  
  // ledAlternate(PIN, PIN2, 500);
  ledPolice(PIN, PIN2);

  bcm2835_close();
  return 0;
}//end main method

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