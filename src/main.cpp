/*
 * AS5050A Encoder library
 * CONNECTIONS:
 * ---
 * POWER:
 * Orange:  VDD
 * Yellow:  GND
 * ---
 * SPI:
 * Green:   MOSI (SPI bus data input)
 * Blue:    MISO (SPI bus data output)
 * Purple:  SCK  (SPI clock)
 */

#include "main.h"
#include "mbed.h"

SPI spi(PB_5, PB_4, PB_3); // mosi, miso, sclk
DigitalOut cs(PA_4);

int main() {
  while(1){
    // Chip must be deselected
    cs = 1;

    // Setup the spi for 8 bit data, high steady state clock,
    // second edge capture, with a 1MHz clock rate
    spi.format(16,1);
    spi.frequency(10000000);

    // Select the device by seting chip select low
    cs = 0;

    // Send 0x8f, the command to read the WHOAMI register
    spi.write(0x3FFF);

    // Send a dummy byte to receive the contents of the WHOAMI register
    // int whoami = spi.write(0x0000);
    // printf("WHOAMI register = 0x%X\n", whoami);

    // Deselect the device
    cs = 1;
    wait_ms(10);
  }
}
