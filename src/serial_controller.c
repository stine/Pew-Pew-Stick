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
#include "serial_controller.h"
#include "pins.h"

void init_controller_serial(void)
{
  // Set SS, SCLK, and PD1 as output.
  DDRB |= (1<<DDB0)|(1<<DDB1);
  DDRD |= (1<<DDD1);

  // Enable SPI, set to Master mode, clock idle low.
  SPCR |= (1<<SPE)|(1<<MSTR);
  SPCR &= ~(1<<CPOL);

  // Set SCK frequency to fOSC/2.
  SPSR |= (1<<SPI2X);

  // Set Clock Inhibit and Parallel Load high by default.
  PORTB |= (1<<PB0);
  PORTD |= (1<<PD1);
}

void get_controller_state_serial(uint8_t pins[NUM_CONTROLLER_STATE_BYTES])
{
  // Set SH/LD low.
  PORTD &= ~(1<<PD1);

  // Simulate a clock tick to initiate Parallel load.
  PORTB &= ~(1<<PB0);
  PORTB |= (1<<PB0);

  // Set SH/LD high.
  PORTD |= (1<<PD1);

  // Drop CLK INH, Load 8 bits from MISO, set CLK INH high again.
  PORTB &= ~(1<<PB0);
  for (unsigned i = 0; i < NUM_CONTROLLER_STATE_BYTES; ++i)
    {
      SPDR = 0x00;
      while (!(SPSR & (1<<SPIF)));
      pins[i] = SPDR;
    }
  PORTB |= (1<<PB0);
}
