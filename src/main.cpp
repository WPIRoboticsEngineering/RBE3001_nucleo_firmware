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

#include "AS5050.h"
#include "mbed.h"

AS5050 enc1(PB_5, PB_4, PB_3, PA_4); // mosi, miso, sclk, cs

int main() {
  while(1){
    printf("Angle = %X\n", enc1.angleDegrees());
    wait_ms(10);
  }
}
