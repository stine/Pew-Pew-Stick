/*
Pew Pew Stick Microcontroller Code
Copyright (c) 2012, Matt Stine
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef __USB_PROFILES_H__
#define __USB_PROFILES_H__

#include <stdint.h>

typedef enum profile {
  SP_PC,
  SP_PS3,
  SP_X360
} Profile;

int get_endpoint_table(
  Profile profile,
  const uint8_t tableOut[]);

int get_descriptor(
  Profile profile,
  uint16_t wValue,
  uint16_t wIndex,
  const uint8_t **descAddrOut,
  uint8_t *descLenOut);

uint8_t get_report_size(
  Profile profile);

int format_report(
  Profile profile,
  uint8_t rawControl[],
  uint8_t rawControlLen,
  uint8_t reportOut[]);

#endif
