/**
 * @file    checksum.cpp
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
 
#include "checksum.h"

bool validateChecksum( uint8_t const *pkt, uint32_t const length )
{
    uint32_t pos = 0;
    uint8_t sum = 0;
    while ( pos < (length-1) )
    {
        sum += *(pkt+pos++);
    }
    sum = 0x0 - sum;
    // return 0 or 1 based on the checksum test
    return (sum == *(pkt+pos)) ? 1 : 0;
}

void calculateChecksum( uint8_t *pkt, uint32_t const length )
{
    uint32_t pos = 0;
    uint8_t sum = 0;
    while ( pos < (length-1) )
    {
        sum += *(pkt+pos++);
    }    
    // put the checksum into the data stream
    *(pkt+pos) = 0x0 - sum;
    
    return;
}

