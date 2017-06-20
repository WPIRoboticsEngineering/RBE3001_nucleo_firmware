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
Ticker pidTimer;
static PIDimp*  pid[numberOfPid];
double kp=1;
double ki=0;
double kd=0;
void runPid(){
  // update all positions fast and together
  for (int i=0;i<numberOfPid;i++)
     pid[i]->updatePosition();
 // next update all control outputs
  for (int i=0;i<numberOfPid;i++)
      pid[i]->updateControl();
}
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
   pidTimer.attach(&runPid, 0.001);
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
   int iterator=0;
   bool direction =true;
    while(1) {
      float current = clock_us();
      current = current/1000.0;
      double time = printer.RunEvery(current);
      if(time>0){
        if(direction)
          iterator++;
        else
          iterator--;
        if(iterator>1000){
          direction=false;
        }
        if(iterator<-1000){
          direction=true;
        }
        for (int i=0;i<numberOfPid;i++)
          pid[i]->SetPIDTimed(iterator, 0);// go to setpoint in 0ms, no interpolation
      }
      for (int i=0;i<numberOfPid;i++) {
        if(time>0)
          printf("Index %i, Angle =  %f\n",i, pid[i]->state.CurrentState);
      }

      for (int i=0;i<numberOfPid;i++){
        if(time>0){
          printf("\nWorking Output = %f Setpoint = %f\n",
                pid[i]->state.OutputSet,
                pid[i]->state.SetPoint);

        }
      }
      wait_ms(1);
    }
 }
