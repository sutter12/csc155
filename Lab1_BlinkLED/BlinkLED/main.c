// blink.c
/*
Compile & Run Instructions:
  -First compile blink.c
    gcc -c blink.c -o blink.o
  -Compile in main method
    gcc -o lab1 main.c blink.o -l bcm2835
  -Run 
    ./lab1

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