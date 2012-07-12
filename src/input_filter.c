/*
  Pew Pew Stick Microcontroller Code
  Copyright (c) 2012, Matt Stine, Brandon Booth
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

#include "input_filter.h"
#include "macros.h"
#include <stdint.h>

static const uint8_t STABILITY_COUNT_THRESHOLD = 20;

void init_input_filter(struct InputFilter* inputFilter)
{
  for (uint8_t i = 0; i < NUM_CONTROLLER_STATE_BYTES; ++i)
  {
    for (uint8_t j = 0; j < BITS_PER_BYTE; ++j)
    {
      inputFilter->inputBitStabilityCounter[i][j] = 0;
    }
  }
}

void filter_input(struct InputFilter* inputFilter, uint8_t inputBits[NUM_CONTROLLER_STATE_BYTES])
{
  for (uint8_t i = 0; i < NUM_CONTROLLER_STATE_BYTES; ++i)
  {
    uint8_t changedBits = inputFilter->lastInputBits[i] ^ inputBits[i];
    for (uint8_t j = 0; j < BITS_PER_BYTE; ++j)
    {
      if (changedBits & (1<<j))
      {
        inputFilter->inputBitStabilityCounter[i][j] = 0;
      }
      else
      {
        if (inputFilter->inputBitStabilityCounter[i][j] == 0xFF)
        {
          // Input is correct and stable, do nothing
        }
        else if (inputFilter->inputBitStabilityCounter[i][j] > STABILITY_COUNT_THRESHOLD)
        {
          inputFilter->inputBitStabilityCounter[i][j] = 0xFF;

          if (inputBits[i] & (1<<j))
          {
            inputFilter->lastTrustedInputBits[i] |= (1<<j);
          }
          else
          {
            inputFilter->lastTrustedInputBits[i] &= ~(1<<j);
          }
        }
        else
        {
          inputFilter->inputBitStabilityCounter[i][j] += 1;
        }
      }
    }
    inputFilter->lastInputBits[i] = inputBits[i];
    inputBits[i] = inputFilter->lastTrustedInputBits[i];
  }
}