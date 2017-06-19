
#include "MyPid.h"

PIDimp::PIDimp(){}
float PIDimp::getPosition( ){
  return 0;
}
void PIDimp::setOutputLocal( float){

}
int PIDimp::resetPosition( int){
  return 0;
}
void PIDimp::onPidConfigureLocal(){

}

void PIDimp::MathCalculationPosition( float currentTime){
   RunAbstractPIDCalc( currentTime);
}
void PIDimp::MathCalculationVelocity( float currentTime){
   MathCalculationVelocityDefault( currentTime);
}

PidLimitEvent* PIDimp::checkPIDLimitEvents(){

  return &currentEvent;
}
float PIDimp::getMs(){

}
