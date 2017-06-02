  /*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include "mbed.h"

DigitalOut myLed(D7);

int main() {
  while(1) {
    myLed = 1;
    wait_ms(10);
    myLed = 0;
    wait_ms(10);
  }
}
