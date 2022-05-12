#include <stdio.h>
#include <bcm2835.h>
#include "Robot.h"

int main(int argc, char **argv) {
    int left_trim = 0;
    int right_trim = 0;
    int right_id = 1;
    int left_id = 0;
    unsigned char addr = 0x60;
    int stop_at_exit = 1;

    init(addr, left_id, right_id, left_trim, right_trim, stop_at_exit);

    forward(150, 1.0);   // Move forward at speed 150 for 1 second.;
    left(200, 0.5);   // Spin left at speed 200 for 0.5 seconds.;
    forward(150, 1.0);   // Repeat the same movement 3 times below...;
    left(200, 0.5);
    forward(150, 1.0);
    left(200, 0.5);
    forward(150, 1.0);
    right(200, 0.5);

    //Spin in place slowly for a few seconds.
    right(100, -1);  // No time is specified so the robot will start spinning forever.;

    bcm2835_delay(500);
    //time.sleep(2.0)   // Pause for a few seconds while the robot spins (you could do
    // other processing here though!).
    
    stop();// Stop the robot from moving.;

    // Now move backwards and spin right a few times.
    backward(150, 1.0);
    right(200, 0.5);
    backward(150, 1.0);
    right(200, 0.5);
    backward(150, 1.0);
    right(200, 0.5);
    backward(150, 1.0);
}//end main method