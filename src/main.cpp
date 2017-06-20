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
 #include "Servo.h"
 #include "mbed.h"
 #include "MyPid.h"
PIDimp * testPid;
double kp=1;
double ki=0;
double kd=0;
 int main() {
   testPid = new PIDimp( new Servo(PC_9, 5),
                         new AS5050(PB_5, PB_4, PB_3, PA_4));
   testPid->setPIDConstants(kp,ki,kd);
   testPid->InitilizePidController();


  //  int loop = 0;
  //  float angle = 0.0;
  //  while(1){
  //    angle = enc1.angleRad();
  //    wait_ms(1);
  //    loop++;
   //
  //    if(loop >= 100) {
  //      printf("Angle = %4.2f\n", angle);
  //      loop = 0;
  //    }
  //  }

    while(1) {
      testPid->updatePosition();
      testPid->updateControl();
        // for(int i=0; i<100; i++) {
        //   myservo.write(i/100.0);
        //     wait(0.01);
        // }
        // for(int i=100; i>0; i--) {
        //     myservo.write(i/100.0);
        //     wait(0.01);
        // }
      }

 }
