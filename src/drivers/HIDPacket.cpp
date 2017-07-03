#include "HIDPacket.h"

HIDSimplePacket::HIDSimplePacket(){
  hid=new USBHID(getNumberOfBytesInPacket(),//uint8_t output_report_length=
     getNumberOfBytesInPacket(), //uint8_t input_report_length=
     0x3742, //uint16_t vendor_id=
     0x0007, // uint16_t product_id=
     0x0001, //uint16_t product_release=
     true);//bool connect=
     recv_report.length=getNumberOfBytesInPacket();
     send_report.length=getNumberOfBytesInPacket();
}

/**
* Non blocking function to check if a packet is availible from the physical layer
*/
 bool HIDSimplePacket::isPacketAvailible(){
   if( hid->readNB(&recv_report)){
     //printf("\nReceived packet");

     return true;
   }
   return false;
 }
/**
* User function that fills the buffer from the data in the physical layer
* this data should already be framed, checksummed and validated as a valid packet
*/
 int32_t HIDSimplePacket::getPacket(uint8_t * buffer,uint32_t numberOfBytes){
       recv_report.length=numberOfBytes;
       for(int i = 0; i < recv_report.length; i++) {
         buffer[i]=recv_report.data[i];
       }
 }
/**
* User function that sends the buffer to the physical layer
* this data should already be framed, checksummed and validated as a valid packet
*/
 int32_t HIDSimplePacket::sendPacket(uint8_t * buffer,uint32_t numberOfBytes){
   //Fill the report
   //printf("\nsending packet");

   send_report.length = numberOfBytes;
   for (int i = 0; i < send_report.length; i++)
       send_report.data[i] = buffer[i];
   //Send the report
   hid->send(&send_report);
 }
