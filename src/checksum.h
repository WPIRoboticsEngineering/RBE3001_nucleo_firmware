/**
 * @file    checksum.h
 * @brief   Utility Function - Data integrity helpers
 * @author  sam grove
 * @version 1.0
 *
 * Copyright (c) 2013
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#ifndef CHECKSUM_H
#define CHECKSUM_H

#include <stdint.h>
 
/** Helpers for working data streams
 *
 * Example:
 * @code
 *  #include "mbed.h"
 *  #include "checksum.h"
 *
 *  DigitalOut myled(LED1);
 *  
 *  template <int T>
 *  struct data{
 *      uint8_t buf[T];
 *      uint8_t checksum;
 *  };
 *  data<12> all_ones = {{1,1,1,1,1,1,1,1,1,1,1,1}};
 *
 *  int main() 
 *  {
 *      calculateChecksum( all_ones.buf, sizeof(all_ones) );
 *      
 *      for(int i=0; i<sizeof(all_ones); i++)
 *      {
 *          printf("%02d: %d\n", i, *(all_ones.buf+i));
 *      }
 *
 *      printf("checksum test: %s\n", (result)?"passed":"failed");
 *
 *      while(1) 
 *      {
 *          myled = 1;
 *          wait(0.2);
 *          myled = 0;
 *          wait(0.2);
 *      }
 *  }
 * @endcode
 */

/** Calculate the checksum of a data stream
 *  Assumes the checksum is in the last position, 8-bits and 0 - the sum of data 
 *  @param pkt - A pointer to the data
 *  @param length - The amount of data that the checksum calculates
 *  @returns true if the checksum is correct and false otherwise
 */
bool validateChecksum( uint8_t const *pkt, uint32_t const length );

/** Calculate and store the checksum into the last position of a data stream
 *
 *  @param pkt - A pointer to the data
 *  @param length - The amount of data that the checksum calculates
 */
void calculateChecksum( uint8_t *pkt, uint32_t const length );

#endif
