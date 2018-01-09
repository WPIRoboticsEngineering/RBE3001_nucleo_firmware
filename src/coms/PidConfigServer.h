/**
 * @file PidServer.h 
 * @brief PidServer for the RBE3001 robotic arm
 * 
 * @section RBE3001 - Nucleo Firmware - PidServer
 *
 * Instructions
 * ------------
 * This class implements a communication server that can be used to 
 * configure the gains of the PID controller. 
 *
 * IMPORTANT - The identifier for this server is the integer number 65.
 *
 */

#ifndef RBE3001_PID_CONFIG
#define RBE3001_PID_CONFIG

#include <PID_Bowler.h>
#include <PacketEvent.h>
#include "../drivers/MyPid.h"
#include <cmath>               // needed for std::abs

#define PIDCONFIG_SERVER_ID 65 // identifier for this server


/**
 *  @brief This class is responsible for updating the gains of the PID 
 *         controller. Desired gains are received through HID from high-level
 *         Matlab code.
 */  
class PidConfigServer: public PacketEventAbstract
{
 private:
  PIDimp ** myPidObjects;
  int myPumberOfPidChannels;
  
 public:
  // Packet ID needs to be set
  PidConfigServer (PIDimp ** pidObjects, int numberOfPidChannels)
    : PacketEventAbstract(PIDCONFIG_SERVER_ID)
  {
    myPidObjects=pidObjects;
    myPumberOfPidChannels=numberOfPidChannels;
  }
  
  // This method is called every time a packet from MATLAB is received
  // via HID
  void event(float * buffer);
};

#endif /* end of include guard: RBE3001_PID_CONFIG */
