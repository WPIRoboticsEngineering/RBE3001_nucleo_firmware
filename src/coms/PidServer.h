#ifndef  Pid_server
#define Pid_server
#include <PID_Bowler.h>
#include <PacketEvent.h>
#include "../drivers/MyPid.h"
#include <cmath>        // std::abs
#define PidServerID 37

class PidServer: public PacketEventAbstract{
private:
  PIDBowler* * myPidObjects;
   int myPumberOfPidChannels;
public:
  // Packet ID needs to be set
  PidServer (PIDBowler* * pidObjects, int numberOfPidChannels )
   : PacketEventAbstract( PidServerID){
    myPidObjects=pidObjects;
    myPumberOfPidChannels=numberOfPidChannels;
  }
  //User function to be called when a packet comes in
  // Buffer contains data from the packet coming in at the start of the function
  // User data is written into the buffer to send it back
  void event(float * buffer);
};


#endif /* end of include guard: Pid_server */
