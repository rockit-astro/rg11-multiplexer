//**********************************************************************************
//  Copyright 2017, 2023 Paul Chote
//  This file is part of rg11-multiplexer, which is free software. It is made
//  available to you under version 3 (or later) of the GNU General Public License,
//  as published by the Free Software Foundation and included in the LICENSE file.
//**********************************************************************************

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "serial.h"

#define BLINKER_LED_DISABLED PORTC &= ~_BV(PC7)
#define BLINKER_LED_ENABLED  PORTC |= _BV(PC7)
#define BLINKER_LED_INIT     DDRC |= _BV(DDC7), BLINKER_LED_DISABLED

// Sensors are connected to PB5,6,7
// Note that PB1,3 are used by serial.c; avoid trampling over their state!
#define SENSOR_PINS          (_BV(PB5) | _BV(PB6) | _BV(PB7))
#define SENSORS_INIT         DDRB &= ~SENSOR_PINS, PORTB |= SENSOR_PINS
#define SENSOR1_SAFE         bit_is_clear(PINB, PINB5)
#define SENSOR2_SAFE         bit_is_clear(PINB, PINB6)
#define SENSOR3_SAFE         bit_is_clear(PINB, PINB7)

// Rate limit the status reports to the host PC to 1Hz
volatile bool update_state = false;

void tick(void)
{
    if (!update_state)
        return;

    cli();
    serial_write(SENSOR1_SAFE ? '0' : '1');
    serial_write(SENSOR2_SAFE ? '0' : '1');
    serial_write(SENSOR3_SAFE ? '0' : '1');
    serial_write('\r');
    serial_write('\n');
    update_state = false;
    sei();
}


int main(void)
{
    // Configure timer1 to interrupt once per second
    OCR1A = 15624;
    TCCR1B = _BV(CS12) | _BV(CS10) | _BV(WGM12);
    TIMSK1 |= _BV(OCIE1A);

    BLINKER_LED_INIT;
    SENSORS_INIT;

    serial_initialize();

    sei();
    for (;;)
        tick();
}

volatile bool led_active;
ISR(TIMER1_COMPA_vect)
{
    // Update the status LED on the arduino to show that the
    // monitoring is still active
    if ((led_active ^= true))
        BLINKER_LED_ENABLED;
    else
        BLINKER_LED_DISABLED;

    update_state = true;
}
