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

#include <avr/io.h>
#include <avr/pgmspace.h>
#include "parallel_controller.h"

void init_controller_parallel(void)
{
  DDRB |= 0; // Configure PortB as an input port
  DDRD |= 0; // Configure PortD as an input port
  PORTB |= (PINB_00 | PINB_01 | PINB_03); // Enable internal pull-up resistors
  PORTD |= (PIND_01);
}

void get_controller_state_parallel(uint8_t pins[NUM_CONTROLLER_STATE_BYTES])
{
  pins[0] = 0;
  pins[1] = 0;
  pins[1] |= (PINB & PINB_00) ? 0 : D_UP;
  pins[1] |= (PINB & PINB_01) ? 0 : D_DN;
  pins[1] |= (PINB & PINB_03) ? 0 : D_LT;
  pins[1] |= (PIND & PIND_01) ? 0 : D_RT;
}
