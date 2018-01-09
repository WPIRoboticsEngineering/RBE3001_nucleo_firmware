/**
 * RBE3001 - Nucleo Firmware
 * See header file for more detail on this class.
 */
#include "PidServer.h"

/**
 *  @brief This function handles incoming HID packets from MATLAB.
 *
 *  @description This method has two parts: in part 1, we will decode the incoming
 *               packet, extract the setpoints and send those values to the 
 *               PID controller; in part 2, we will generate a response that will be
 *               sent back to MATLAB through HID. This is useful to e.g. send sensor
 *               data to MATLAB for plotting.
 */  
void PidServer::event(float * packet){

  /*
   * ======= PART 1: Decode setpoints and send commands to the PID controller ==
   */
  
  bool skipLink = false; //!FIXME Do we need this? If not, let's get rid of it
  
  for (int i = 0; i < myPumberOfPidChannels; i++)
    {      
      // extract the three setpoint values (one for each joint) from the packet buffer
      float setpoint = packet[(i*3)+0];
      float velocityTarget = 0; // this is currently unused
      float forceTarget = 0;    // this is currently unused
      //printf("\r\n %i : %f", i,setpoint);
      // get current position from arm 
      float position = myPidObjects[i]->GetPIDPosition();
      
      // now let's initiate motion to the setpoints

      // !FIXME I am not sure what the next two instructions are for.
      //        The if statement below always returns false and therefore we never
      //        enter the clause. Is this code needed? If not, let's get rid of it.
      float timeOfMotion = 0;
      if(velocityTarget>0)
	timeOfMotion=(std::abs(setpoint-position)/velocityTarget)*1000;// convert from Tics per second to miliseconds

      // !FIXME what is the `bound' method doing?
      bool newUpdate = !myPidObjects[i]->bound(setpoint,
					       myPidObjects[i]->state.interpolate.set,
					       0.01,   // !FIXME need to explain what these constants are
					       0.01);
      
      if(newUpdate)
	{
	  // disable interrupts first
	  __disable_irq();
	  myPidObjects[i]->SetPIDEnabled(true); // !FIXME Do we need to do this
	                                        //  every time?
	                                        // Can't we just leave it enabled?

	  // go to setpoint in timeBetweenPrints ms, linear interpolation
	  myPidObjects[i]->SetPIDTimed(setpoint, timeOfMotion); // !FIXME what is `timeBetweenPrints'?

	  // re-enable interrupts
	__enable_irq();
	
	}
      
      else // !FIXME The following clause does not seem to be doing anything.
	   //        Do we need to keep it?
	{
	  //  printf("\r\nPacket write ignored, index %i to %f is already %f",i,setpoint,myPidObjects[i]->state.interpolate.set);
	  skipLink=true;
	}
      //  if(skipLink){
      //    for (int i=0;i<15;i++){
      //      printf("\r\nPacket write ignored, value %i to %f ",i,packet[i]);
      //    }
      //}
    }

  /*
   * ======= PART 2: Generate a response to be sent back to MATLAB =============
   */

  // we will be using the same memory area in which the incoming packet was stored,
  // however, a we need to perform a type cast first (for convenience).
  uint8_t * buff = (uint8_t *) packet;

  // re-initialize the packet to all zeros
  for(int i = 4; i < 64;i++)
      buff[i]=0;
  
  /**
   * The following loop reads sensor data (encoders ticks, joint velocities and
   * force readings) and writes it in the response packet.
   */
  for(int i = 0; i < myPumberOfPidChannels; i++)
    {
      float position = myPidObjects[i]->GetPIDPosition();
      float velocity = myPidObjects[i]->getVelocity();
      float torque   = myPidObjects[i]->loadCell->read();

      packet[(i*3)+0] = position;
      packet[(i*3)+1] = velocity;
      packet[(i*3)+2] = torque; 
    }
}
