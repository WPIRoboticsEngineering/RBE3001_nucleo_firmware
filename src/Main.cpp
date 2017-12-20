#include "main.h"

#define  numberOfPid  3
//#define DUMMYLINKS
// reportLength max size is 64 for HID
Ticker pidTimer;
static PIDimp*  pid[numberOfPid];
HIDSimplePacket coms;
float  calibrations[3] = {0,0,0};
//float  calibrations[3] = {114,784,-10};
Servo * gripper;

void runPid(){
  // update all positions fast and together
  for (int i=0;i<numberOfPid;i++)
     pid[i]->updatePosition();
 // next update all control outputs
  for (int i=0;i<numberOfPid;i++)
      pid[i]->updateControl();
}
int main() {
	printf("\r\n\r\n Top of Main \r\n\r\n");

#if defined(DUMMYLINKS)
   pid[0] =(PIDimp*) new DummyPID();
   pid[1] =(PIDimp*) new DummyPID();
   pid[2] =(PIDimp*) new DummyPID();
#else
#if defined( REV1)
   SPI * spiDev = new SPI(MOSI, MISO, CLK);
   SPI * spi3 = spiDev;
   SPI * spi4 = spiDev;
   SPI * spi5 = spiDev;
#else if defined(REV2)
   SPI * spi3 = new SPI(PC_12, PC_11, PC_10); // spi(mosi, miso, clk)
   SPI * spi4 = new SPI(PE_6, PE_5, PE_2); // spi(mosi, miso, clk)
   SPI * spi5 = new SPI(PF_9, PF_8, PF_7); // spi(mosi, miso, clk)
#endif
   pid[0] = new PIDimp( new Servo(SERVO_1, 5),
                         new AS5050(spi3, ENC_1));  // mosi, miso, sclk, cs
   pid[1] = new PIDimp( new Servo(SERVO_2, 5),
                         new AS5050(spi4, ENC_2));  // mosi, miso, sclk, cs
   pid[2] = new PIDimp( new Servo(SERVO_3, 5),
                         new AS5050(spi5, ENC_3));  // mosi, miso, sclk, cs
#endif
   gripper=new Servo(GRIPPER_SERVO, 5);
   // Invert the direction of the motor vs the input
   //pid[0]->state.config.Polarity = true;
   for (int i=0;i<numberOfPid;i++){
     pid[i]->state.config.Enabled=false;// disable PID to start with
   }
   wait_ms(500);// Cosines delay
   pidTimer.attach(&runPid, 0.005);
   // capture 100 ms of encoders before starting
   wait_ms(100);
	for (int i = 0; i < numberOfPid; i++) {
		//reset after encoders have been updated a few times
		pid[i]->InitilizePidController();
#if defined(DUMMYLINKS)
		pid[i]->ZeroPID();   // set the current encoder value to 0
							 // this should be replaced by calibration routine
#else
		//apply calibrations
		pid[i]->pidReset(pid[i]->GetPIDPosition()-calibrations[i]);
#endif
		if(pid[i]->GetPIDPosition()>3000) {
			pid[i]->pidReset(pid[i]->GetPIDPosition()-4095);
		}
		pid[i]->SetPIDEnabled(true);              // Enable PID to start control
		pid[i]->SetPIDTimed(pid[i]->GetPIDPosition(), 1000);
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
   coms.attach(new DummyServer ());
   coms.attach(new PidServer (pid, numberOfPid ));
   printf("\r\n\r\n Starting Core \r\n\r\n");
   RunEveryObject* print = new RunEveryObject(0,500);
    while(1) {
        coms.server();
        if(print->RunEvery(pid[0]->getMs())>0){
          printf("\r\nEncoder Value = %f , %f , %f",
          pid[0]->GetPIDPosition(),
          pid[1]->GetPIDPosition(),
          pid[2]->GetPIDPosition());
        }


    }
}
