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
double kp=0.01;
double ki=0;
double kd=0;

void runPid(){
  // update all positions fast and together
  for (int i=0;i<numberOfPid;i++)
     pid[i]->updatePosition();
 // next update all control outputs
  for (int i=0;i<numberOfPid;i++)
      pid[i]->updateControl();
//Handle any chip errors after the critical timing
  // for (int i=0;i<numberOfPid;i++)
  //     if(pid[i]->encoder->error.status)
  //       pid[i]->encoder->handleErrors();

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
     pid[i]->ZeroPID();// set the current encoder value to 0
                       // this should be replaced by calibration routine
     pid[i]->SetPIDEnabled( true);// Enable PID to start control
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
   float timeBetweenPrints = 2000;
   float bounds = 500;
   RunEveryObject printer(0,1000);
   RunEveryObject setpoint(0,timeBetweenPrints);
   float iterator=0;
   bool direction =true;
   printf("\n\n Starting Core \n\n");
    while(1) {
      float current = pid[0]->getMs();
      float time = printer.RunEvery(current);

      // if(time>0){
      //   printf("\n\n____________________\n Setpoint %i Time =  %f Seconds\n",
      //     iterator,
      //     (current/1000.0));
      //     for (int i=0;i<numberOfPid;i++){
      //       //println_E("Time= ");p_fl_E(  pid[i]->state.interpolate.currentTime);
      //       // print_W(" Set= ");p_fl_W(pid[i]->state.interpolate.set);
      //       // print_E(" start= ");p_fl_E(pid[i]->state.interpolate.start);
      //       // print_W(" setTime= ");p_fl_W(pid[i]->state.interpolate.setTime);
      //       // print_E(" startTime= ");p_fl_E(pid[i]->state.interpolate.startTime);
      //       //
      //       // println_W("elapsedTime = ");p_fl_W(pid[i]->state.interpolate.elapsed);
      //       // print_E(" incremental distance = ");p_fl_E(pid[i]->state.interpolate.currentDistance);
      //       // print_W(" Target = ");p_fl_W(pid[i]->state.interpolate.currentLocation);
      //     }
      //
      // }
      //for (int i=0;i<numberOfPid;i++) {

        if(setpoint.RunEvery(current)>0){

          if(direction)
            iterator+=bounds/3;
          else
            iterator-=bounds/3;
          if(iterator>bounds){
            direction=false;
          }
          if(iterator<-bounds){
            direction=true;
          }

          for (int i=0;i<numberOfPid;i++){
            __disable_irq();    // Disable Interrupts
            if(direction)
              pid[i]->SetPIDTimed(iterator, timeBetweenPrints);// go to setpoint in timeBetweenPrints ms, no interpolation
            else
              pid[i]->SetPIDTimed(iterator, 0);// go to setpoint in timeBetweenPrints ms, no interpolation

            __enable_irq();     // Enable Interrupts

          }
          printf("\n\nUpdating setpoint %f\n\n",iterator);
        }

    //  }

      // for (int i=0;i<numberOfPid;i++){
        if(time>0){
          // printf("\nOutput = %f Setpoint = %f Angle =  %f ",
          //       pid[0]->state.Output,
          //       pid[0]->state.SetPoint,
          //     pid[0]->state.CurrentState);

        }
      // }
      wait_ms(1);
    }
 }
