Firmware for an Arduino board that monitors the state of 3 RG11 rain sensors and reports the status over a UART/RS232 output once per second.

### Compilation/Installation

Requires a working `avr-gcc` installation.
* On macOS add the `osx-cross/avr` Homebrew tap then install the `avr-gcc`, `avr-libc`, `avr-binutils`, `avrdude` packages.
* On Ubuntu install the `gcc-avr`, `avr-libc`, `binutils-avr`, `avrdude` packages.
* On Windows WinAVR should work.

First update the `Makefile` to define `MAX_SHUTTER_CLOSE_STEPS` for the desired dome and then compile using `make`.
Removing the Arduino Micro from the base board (it won't work if attached) and then quickly double pressing the reset button to put the board into its update mode (the LED should fade in and out).  Run `make install` within 8 seconds to install the firmware.