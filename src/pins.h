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

#ifndef __PINS_H__
#define __PINS_H__

/* Number of bytes to describe all inputs over SPI */
#define MSG_LEN_BYTES 2

/* First Byte over SPI */
#define B_05 (1<<7)
#define B_06 (1<<6)
#define B_07 (1<<5)
#define B_08 (1<<4)
#define B_09 (1<<3)
#define B_10 (1<<2)
#define B_11 (1<<1)
#define B_12 (1<<0)

/* Second Byte over SPI */
#define D_LT (1<<7)
#define D_RT (1<<6)
#define D_UP (1<<5)
#define D_DN (1<<4)
#define B_01 (1<<3)
#define B_02 (1<<2)
#define B_03 (1<<1)
#define B_04 (1<<0)

/* Axis values over USB */
#define DIR_NULL (128)
#define DIR_LEFT (0)
#define DIR_RIGHT (255)
#define DIR_UP (0)
#define DIR_DOWN (255)

/* Button values over USB (two bytes) */
#define BUTTON_01 (1<<0)
#define BUTTON_02 (1<<1)
#define BUTTON_03 (1<<2)
#define BUTTON_04 (1<<3)
#define BUTTON_05 (1<<4)
#define BUTTON_06 (1<<5)
#define BUTTON_07 (1<<6)
#define BUTTON_08 (1<<7)
#define BUTTON_09 (1<<0)
#define BUTTON_10 (1<<1)
#define BUTTON_11 (1<<2)
#define BUTTON_12 (1<<3)

#endif
