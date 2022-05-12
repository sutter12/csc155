// input.c
//
// Example program for bcm2835 library
// Reads and prints the state of an input pin
//
// gcc -o input input.c -l bcm2835
// sudo ./input
//
// Author: Alexander Sutter

#include <bcm2835.h>
#include <stdio.h>

// Input on RPi pin GPIO 15
#define PIN RPI_GPIO_P1_11

int main(int argc, char **argv) {
    // If you call this, it will not actually access the GPIO
    // Use for testing
    // bcm2835_set_debug(1);

    if (!bcm2835_init())
	return 1;

    // Set RPI pin P1-15 to be an input
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_INPT);
    //  with a pullup
    bcm2835_gpio_set_pud(PIN, BCM2835_GPIO_PUD_UP);

    // Blink
    while (1) {
        // Read some data
        uint8_t value = bcm2835_gpio_lev(PIN);
        printf("read from pin 15: %d\n", value);
        
        // wait a bit
        delay(500);
    }//end while loop

    bcm2835_close();
    return 0;
}//end main method

