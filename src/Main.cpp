#include "AS5050.h"
#include "Servo.h"
#include "mbed.h"
#include "MyPid.h"
#include "main.h"
#include "USBHID.h"

#define  numberOfPid  3
// reportLength max size is 64 for HID
#define  reportLength 64
Ticker pidTimer;
static PIDimp*  pid[numberOfPid];
USBHID hid(reportLength,//uint8_t output_report_length=
   reportLength, //uint8_t input_report_length=
   0x3742, //uint16_t vendor_id=
   0x0007, // uint16_t product_id=
   0x0001, //uint16_t product_release=
   true);//bool connect=
//This report will contain data to be sent
HID_REPORT send_report;
HID_REPORT recv_report;
void updateHID(){
  //Fill the report
      send_report.length = reportLength;
      for (int i = 0; i < send_report.length; i++)
          send_report.data[i] = rand() & 0xff;

      //Send the report
      hid.send(&send_report);

      //try to read a msg
      if(hid.readNB(&recv_report)) {
          for(int i = 0; i < recv_report.length; i++) {
              printf("%d ", recv_report.data[i]);
          }
          printf("\r\n");
      }
}
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
   pidTimer.attach(&runPid, 0.004);
   // capture 100 ms of encoders before starting
   wait_ms(100);
   for (int i=0;i<numberOfPid;i++){
     //reset after encoders have been updated a few times
     pid[i]->InitilizePidController();
     if(pid[i]->GetPIDPosition()>2048){
       pid[i]->pidReset(pid[i]->GetPIDPosition()-4095);
     }
     //pid[i]->ZeroPID();// set the current encoder value to 0
                       // this should be replaced by calibration routine
     pid[i]->SetPIDEnabled( true);// Enable PID to start control
    }

   /*
   // Run PID controller calibration
   // only one can be run at a time, and the control loop needs to wait
   // until the calibration is done before advancing to the next
   pid[0]->runPidHysterisisCalibration();
   // Run a homing procedure down where 123 is the value of the encoder at home
   pid[0]->startHomingLink( CALIBRARTION_home_down, 123);
   // Run a homing procedure up  where 123 is the value of the encoder at home
   pid[0]->startHomingLink( CALIBRARTION_home_up, 123);
   // Run a homing procedure to scale the velocity outputs  where 123 is the value of the encoder at home
   pid[0]->startHomingLink( CALIBRARTION_home_velocity, 123);
   */
   float timeBetweenPrints = 2000;
   float bounds = 800;
   RunEveryObject printer(0,1000);
   RunEveryObject setpoint(0,timeBetweenPrints);
   float iterator=0;
   bool direction =true;
   printf("\n\n Starting Core \n\n");
    while(1) {
      float current = pid[0]->getMs();
      // this is a spaced out timer object used to simplify timed events with a single timer and single thread
        if(setpoint.RunEvery(current)>0){
          // sweep some setpoints
          if(direction)
            iterator+=bounds/4;
          else
            iterator-=bounds/4;

          printf("\n\nUpdating setpoint %f Position %f Control output %f Motor Set %f\n\n",
            iterator,
            pid[0]->GetPIDPosition(),
            pid[0]->state.Output,
            pid[0]->state.OutputSet
          );
          for (int i=0;i<numberOfPid;i++){
            //Interrupts need to be disabled to to avoid conflicts with pid objects
            __disable_irq();    // Disable Interrupts
            if(direction)
              pid[i]->SetPIDTimed(iterator, timeBetweenPrints);// go to setpoint in timeBetweenPrints ms, linear interpolation
            else
              pid[i]->SetPIDTimed(iterator, 0);// go to setpoint in 0 ms, no interpolation
            __enable_irq();     // Enable Interrupts

          }
          if(iterator>bounds){
            direction=false;
          }
          if(iterator<-bounds){
            direction=true;
          }

        }
      updateHID();
      wait_ms(100);
    }
 }
