Firmware for an Arduino board that injects the state of 3 RG11 rain sensors into the serial data stream from a Vaisala WXT530 weather station.

### Compilation/Installation

Requires a working `avr-gcc` installation.
* On macOS add the `osx-cross/avr` Homebrew tap then install the `avr-gcc`, `avr-libc`, `avr-binutils`, `avrdude` packages.
* On Ubuntu install the `gcc-avr`, `avr-libc`, `binutils-avr`, `avrdude` packages.
* On Windows WinAVR should work.
