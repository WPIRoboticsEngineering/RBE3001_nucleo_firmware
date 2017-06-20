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
#include "main.h"
#define  numberOfPid  3

static PIDimp*  pid[numberOfPid];
double kp=1;
double ki=0;
double kd=0;

 int main() {

   pid[0] = new PIDimp( new Servo(SERVO_1, 5),
                         new AS5050(MOSI, MISO, CLK, ENC_1));  // mosi, miso, sclk, cs
   pid[1] = new PIDimp( new Servo(SERVO_2, 5),
                         new AS5050(MOSI, MISO, CLK, ENC_2));  // mosi, miso, sclk, cs
   pid[2] = new PIDimp( new Servo(SERVO_3, 5),
                         new AS5050(MOSI, MISO, CLK, ENC_3));  // mosi, miso, sclk, cs
   // Invert the direction of the motor vs the input
   //pid[0]->state.config.Polarity = true;
   for (int i=0;i<numberOfPid;i++){
     pid[i]->setPIDConstants(kp,ki,kd);
     pid[i]->InitilizePidController();
   }
   /*
   // Run PID controller calibration
   pid[0]->runPidHysterisisCalibration();
   // Run a homing procedure down
   pid[0]->startHomingLink( CALIBRARTION_home_down, 123);
   // Run a homing procedure up
   pid[0]->startHomingLink( CALIBRARTION_home_up, 123);
   // Run a homing procedure to scale the velocity outputs
   pid[0]->startHomingLink( CALIBRARTION_home_velocity, 123);
   */
   RunEveryObject printer(0,5000);
    while(1) {
      // update all positions fast and together
      float current = clock_us();
      current = current/1000.0;
      double time = printer.RunEvery(current);
      for (int i=0;i<numberOfPid;i++) {
        pid[i]->updatePosition();
        if(time>0)
          printf("Index %i, Angle =  %f\n",i, pid[i]->state.CurrentState);
      }
      if(time>0)
        printf("\nUpdateing control ");
      // next update all control outputs
      for (int i=0;i<numberOfPid;i++){
        if(time>0)
          printf("\nWorking Output = %f\n", pid[i]->state.OutputSet);
        pid[i]->updateControl();
      }
      wait_ms(1);
    }
 }
