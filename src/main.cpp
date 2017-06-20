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
#define  numberOfPid  3

static PIDimp*  pid[numberOfPid];
double kp=1;
double ki=0;
double kd=0;

 int main() {
   pid[0] = new PIDimp( new Servo(PC_9, 5),
                         new AS5050(PB_5, PB_4, PB_3, PA_4));
   pid[1] = new PIDimp( new Servo(PC_10, 5),
                         new AS5050(PB_5, PB_4, PB_3, PA_3));
   pid[2] = new PIDimp( new Servo(PC_11, 5),
                         new AS5050(PB_5, PB_4, PB_3, PA_2));
   // Invert the direction of the motor vs the input
   //pid[0]->state.config.Polarity = true;

   for (int i=0;i<numberOfPid;i++){
     pid[i]->setPIDConstants(kp,ki,kd);
     pid[i]->InitilizePidController();
   }
   // Run PID controller calibration
   //pid[0]->runPidHysterisisCalibration();
   // Run a homing procedure down
   //pid[0]->startHomingLink( CALIBRARTION_home_down, 123);
   // Run a homing procedure up
   //pid[0]->startHomingLink( CALIBRARTION_home_up, 123);
   // Run a homing procedure to scale the velocity outputs
   //pid[0]->startHomingLink( CALIBRARTION_home_velocity, 123);
    while(1) {
      // update all positions fast and together
      for (int i=0;i<numberOfPid;i++)
        pid[i]->updatePosition();
      // next update all control outputs
      for (int i=0;i<numberOfPid;i++)
        pid[i]->updateControl();
      wait_ms(1);
    }
 }
