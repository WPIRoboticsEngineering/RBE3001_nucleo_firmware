#ifndef  VelocityTarget_h
#define VelocityTarget_h
#include <PID_Bowler.h>
#include <PacketEvent.h>
#include "../drivers/MyPid.h"
#include <cmath>        // std::abs


class VelocityTarget: public PacketEventAbstract{
private:
  PIDBowler* * myPidObjects;
   int myPumberOfPidChannels;
public:
  // Packet ID needs to be set
   VelocityTarget (PIDBowler* * pidObjects, int numberOfPidChannels )
   : PacketEventAbstract( 42){
    myPidObjects=pidObjects;
    myPumberOfPidChannels=numberOfPidChannels;
  }
  //User function to be called when a packet comes in
  // Buffer contains data from the packet coming in at the start of the function
  // User data is written into the buffer to send it back
  void event(float * buffer);
};


#endif /* end of include guard: Pid_server */
