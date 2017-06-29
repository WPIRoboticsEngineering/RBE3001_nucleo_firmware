#include "mbed.h"
#include "checksum.h"
#include "USBSerial.h"

DigitalOut myled(LED1);
USBSerial serial;

template <int T>
struct data{
    uint8_t buf[T];
    uint8_t checksum;
};

int len = 12;
data<12> all_ones = {{' ', ' ',' ',' ',' ',' ','d','e','r','p','\n','\r'}};
const event_callback_t callback(){
  // std::cout<<"sending this shiz"<<std::endl;
}
int main()
{
    calculateChecksum( all_ones.buf, sizeof(all_ones) );

    while(1)
    {
      for(int i = 0; i<len;i++) {
        serial.putc(all_ones.buf[i]);
      }
        myled = 1;
        wait(0.2);
        myled = 0;
        wait(0.2);
    }
}
