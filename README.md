# Piano2040

This is a firmware for a DIY piano keyboard using an RP2040 microcontroller. It supports USB MIDI and PC keyboard outputs, as well as a debug mode using USB serial.

This is based on ravinrabbid's [DivaCon2040](https://github.com/ravinrabbid/DivaCon2040). It's heavily cut down as I was not interested in controller support, display, etc, but DivaCon2040 provided excellent bones for MIDI and keyboard. Thank you for the well structured project!

## Building
If you need to make any adjustments to my configuration, `include/GlobalConfiguration.h` has most of the settings you would need. See [SCHEMATIC.md](SCHEMATIC.md) for how everything is wired by default.

Hold the leftmost 'C' key while plugging in the keyboard to enter flash mode.

### VSCode (Windows, Linux, MacOS)
Install [VSCode](https://code.visualstudio.com/) and get the [Raspberry Pi Pico](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico) extension. From the extension choose 'Import Project' and select the folder where you've checked out this repository, then use 'Compile Project'.

### CLI
See [pico-sdk readme](https://github.com/raspberrypi/pico-sdk/blob/master/README.md#quick-start-your-own-project) for a list of pre-requisites.

Use the environment variables `PICO_SDK_PATH` to use a local pico-sdk, and `PICO_BOARD` to select another target board.
By default the pico-sdk will be fetched from Github and the target board will be "pico".

```sh
mkdir build && cd build
cmake ..
make
```
