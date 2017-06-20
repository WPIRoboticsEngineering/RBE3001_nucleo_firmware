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
double kp=0.1;
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
     pid[i]->state.config.Enabled=false;// disable PID to start with
   }
   pidTimer.attach(&runPid, 0.001);
   // capture 100 ms of encoders before starting
   wait_ms(100);
   for (int i=0;i<numberOfPid;i++){
     pid[i]->setPIDConstants(kp,ki,kd);
     //reset after encoders have been updated a few times
     pid[i]->InitilizePidController();
     pid[i]->state.config.Enabled=true;// Enable PID to start control
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
   float timeBetweenPrints = 5000;
   RunEveryObject printer(0,1000);
   RunEveryObject setpoint(0,timeBetweenPrints);
   int iterator=0;
   bool direction =true;
    while(1) {
      float current = pid[0]->getMs();
      float time = printer.RunEvery(current);
      if(setpoint.RunEvery(current)>0){

        if(direction)
          iterator++;
        else
          iterator--;
        if(iterator>10){
          direction=false;
        }
        if(iterator<-10){
          direction=true;
        }
        printf("Updating setpoint %i"+iterator);
        for (int i=0;i<numberOfPid;i++)
          pid[i]->SetPIDTimed(iterator, 2000);// go to setpoint in timeBetweenPrints ms, no interpolation
      }
      if(time>0){
        printf("\n\n____________________\n Setpoint %i Time =  %f Seconds\n",
          iterator,
          (current/1000.0));

      }
      for (int i=0;i<numberOfPid;i++) {
        if(time>0)
          printf("Index %i, Angle =  %f\n",i, pid[i]->GetPIDPosition());
      }

      for (int i=0;i<numberOfPid;i++){
        if(time>0){
          printf("\nWorking Output = %f Setpoint = %f",
                pid[i]->state.Output,
                pid[i]->state.SetPoint);

        }
      }
      wait_ms(1);
    }
 }
