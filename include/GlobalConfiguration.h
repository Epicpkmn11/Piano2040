// The structure of this file is a little weird,
// first off, we define constants used in
// non-C++ code:
#define OCTAVE_COUNT 3
#define MIDI_SHIFT 4

// Now we've got the constants for C++ code, but
// we need these constants for Keys.h to work
// and need Keys.h for this file to work.
// So just the constants for now:
#ifdef __cplusplus
#ifndef GLOBALCONFIGURATION_H_CONSTANTS
#define GLOBALCONFIGURATION_H_CONSTANTS

#include "usb/device_driver.h"

namespace Piano2040::Config {

const int octave_count = OCTAVE_COUNT;
const int sleep_us = 1;
const usb_mode_t usb_mode = USB_MODE_MIDI;

} // namespace Piano2040::Config

#endif // GLOBALCONFIGURATION_H_CONSTANTS

// Alright, now we get to the part that depends
// on Keys.h. Pin config and such here:
#ifndef GLOBALCONFIGURATION_ONLY_CONSTANTS

#ifndef GLOBALCONFIGURATION_H_PERIPHERALS
#define GLOBALCONFIGURATION_H_PERIPHERALS

#include "peripherals/Keys.h"

namespace Piano2040::Config {

const Peripherals::Keys::Config buttons_config = {
	.pins = {
		.keys = {
			0,
			1,
			2,
			3,
			4,
			5,
			6,
			7,
			8,
			9,
			10,
			11,
			12
		},
		.octaves = {
			14,
			15,
			26
		},
	},
	.debounce_delay_ms = 3,
};

} // namespace Piano2040::Config

#endif // GLOBALCONFIGURATION_H_PERIPHERALS

#endif // GLOBALCONFIGURATION_ONLY_CONSTANTS

#endif // __cplusplus
