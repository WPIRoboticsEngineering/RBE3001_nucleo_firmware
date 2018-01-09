/**
 * RBE3001 - Nucleo Firmware
 *
 * Instructions
 * ------------
 * Welcome! This is the main file of the Nucleo C++ firmware.
 * The code in this source file starts all the control and communication loops 
 * required to control the arm. Please, take some time to familiarize yourself with the
 * workflow of the program.
 *
 * IMPORTANT - this program has two distinct running modes:
 * **Dummy mode** to be used for firmware testing/debugging when no arm is connected.
 * **Physical mode** to be used when the robotic arm is connected to the Nucleo board.
 *
 * The running mode can be selected at compile time by commenting/uncommenting the
 * DUMMYMODE macro below.
 *
 */
#include "main.h"
#define  DOFs  3     // this macro defines the number of joints of the robotic arm
#define  DUMMYMODE   // this macro selects the running mode - see instructions above

//#define  DEBUG       // if defined, this macro enables the printing of debug
                     // statements to the serial port - which can be read with PUTTY

/*
 * ======= PART 1: Global Variables and definition of ancillary functions ======
 */
Ticker pidTimer;           // implements a timer
static PIDimp * pid[DOFs]; // pointer to PID controllers (one for each link)
HIDSimplePacket coms;      // HID packet handlers

// The following array contains the "home" positions (in encoder ticks) for each
// of the robot's joints 
float homePosition[3] = {361,42,2755};

void runPid() {
	// update all positions fast and together
	for (int i = 0; i < DOFs; i++)
		pid[i]->updatePosition();
	// next update all control outputs
	for (int i = 0; i < DOFs; i++)
		pid[i]->updateControl();
}


/*
 * ======= PART 2: Main file ===================================================
 */
int main() {

#ifdef DEBUG
  printf("\r\n\r\n RBE3001 Arm Firmware \r\n\r\n");
  printf("\r\n\r\n Initializing... \r\n\r\n");
#endif

  /*
   * ======= PART 2a: Initialize PID control ===================================
   * In this section we instantiate objects that implement PID control for
   * each of the joints.
   */

#ifdef DUMMYMODE
  for (int i = 0; i < 3; i++)
    pid[i] = (PIDimp*) new DummyPID();
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
                         new AS5050(spi3, ENC_1),new AnalogIn(LOAD_1));  // mosi, miso, sclk, cs
   pid[1] = new PIDimp( new Servo(SERVO_2, 5),
                         new AS5050(spi4, ENC_2),new AnalogIn(LOAD_2));  // mosi, miso, sclk, cs
   pid[2] = new PIDimp( new Servo(SERVO_3, 5),
                         new AS5050(spi5, ENC_3),new AnalogIn(LOAD_3));  // mosi, miso, sclk, cs
#endif

  RunEveryObject * print = new RunEveryObject(0, 100);

  // disable PID
  for (int i = 0; i < DOFs; i++)
    pid[i]->state.config.Enabled = false;

  // Cosines delay
  wait_ms(500);   
  pidTimer.attach(&runPid, 0.0025);

  // capture 100 ms of encoders before starting
  wait_ms(100);

  for (int i = 0; i < DOFs; i++) // for each joint,
    {
      // reset the PID control after encoders have been updated a few times
      pid[i]->InitilizePidController();
      
      // we will now "zero" the encoder readings
#ifdef DUMMYMODE // if operating in Dummy Mode, set the initial encoder reading to zero
      pid[i]->ZeroPID();   
#else            // else, use the values in homePosition 
      pid[i]->pidReset(pid[i]->GetPIDPosition() - homePosition[i]);
#endif
      
      // !FIXME Do we need the following two instructions? I'm afraid this may generate
      // strange behaviors.
      if (pid[i]->GetPIDPosition() > 3000) 
	pid[i]->pidReset(pid[i]->GetPIDPosition() - 4095);
      
      // Finally, enable PID control
      pid[i]->SetPIDEnabled(true);
      pid[i]->SetPIDTimed(pid[i]->GetPIDPosition(), 1000); // !FIXME What does this instruction do?
    }
  

  /*
   * ======= PART 2b: Initialize HID communication =============================
   * In this section we instatiate objects that handle the communication between
   * this firmware and MATLAB. Each of thess objects implements a server that responds
   * to commands sent over HID. During RBE3001, you will be asked to 
   * implement your own communication servers. To instantiate a new server, use the
   * template below:
   * 
   * coms.attach(new 'MyServerName'(pid, DOFs));
   *
   * C++ classes that define servers should be placed under /src/coms
   *
   * IMPORTANT: when adding a new server, do not forget to add its definition
   *            by including the relevant header file at the beginning of this
   *            source file
   */
  
  coms.attach(new PidServer(pid, DOFs));
  //coms.attach(new PidConfigServer(pid, DOFs));

#ifdef DEBUG
  printf("\r\n\r\n Initialization complete. \r\n\r\n");
  printf("\r\n\r\n Starting main loop... \r\n\r\n");
#endif

  /*
   * ======= PART 2c: Main loop ================================================
   * We are now ready to run the main loop of the firmware. The most important 
   * instruction within the main loop is `coms.server()'. This method, which is 
   * invoked at each loop iteration, results in the execution of the `event()'
   * method on each communication object that was instantiated above
   * (see Part 2b of source file). The `event()' method implements upstream/downstream
   * communication between this firmware and MATLAB - for more information on this 
   * topic, see the example provided in /src/coms/PidServer.cpp.
   *
   * IMPORTANT: the code below includes print statements that, while being useful for 
   *            debugging/testing, will slow down the main loop execution rate.
   *            You can disable these statements at compile time, by commenting out 
   *            the DEBUG macro at the beginning of this source file.
   */
  
  while (1) {

    coms.server();

    // The following code prints out debug statements.
#ifdef DEBUG
    int link = 1;

    if (1) // !FIXME why do we need this if statement?
      {
	// print encoder values for each joint
	printf("\r\nEncoder Value = %f , %f , %f",
	       pid[0]->GetPIDPosition(),
	       pid[1]->GetPIDPosition(),
	       pid[2]->GetPIDPosition());

	// print load cell readings
	printf("\r\nLoad Value = %f , %f , %f",
	       pid[0]->loadCell->read(),
	       pid[1]->loadCell->read(),
	       pid[2]->loadCell->read());
      }
#endif // DEBUG

  }

}
