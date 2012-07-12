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

#ifndef __INPUT_FILTER__
#define __INPUT_FILTER__

#include "pins.h"
#include "macros.h"
#include <stdint.h>

// Filters raw input from external mechanical devices.  Currently the code
// only filters out jitter in the input data due to bouncing (switches).

struct InputFilter
{
  // Stores the state for each bit that was trusted as valid/stable input.
  uint8_t lastTrustedInputBits[NUM_CONTROLLER_STATE_BYTES];

  // Stores the previous state for each bit of input.
  uint8_t lastInputBits[NUM_CONTROLLER_STATE_BYTES];

  // Stores the number of times each input bit has matched the previous
  // input bit state.  A value of 0xFF means the current bit value
  // has not changed and is valid.
  uint8_t inputBitStabilityCounter[NUM_CONTROLLER_STATE_BYTES][BITS_PER_BYTE];
};

// Initializes the passed in input filter.
void init_input_filter(struct InputFilter* inputFilter);

// Takes the raw input bit data and filters it, then overwrites the inputBits array with
// the result.
void filter_input(struct InputFilter* inputFilter, uint8_t inputBits[NUM_CONTROLLER_STATE_BYTES]);

#endif //#ifndef __INPUT_FILTER__