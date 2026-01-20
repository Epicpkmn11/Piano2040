#include "peripherals/Keys.h"
#include "usb/device_driver.h"
#include "utils/InputReport.h"
#include "utils/InputState.h"

#include "GlobalConfiguration.h"

#include "pico/bootrom.h"
#include "pico/stdlib.h"
#include "pico/util/queue.h"

#include <cstdio>
#include <memory>

using namespace Piano2040;

int main() {
	stdio_init_all();

	Peripherals::Keys keys(Config::buttons_config);
	Utils::InputReport input_report;
	Utils::InputState input_state;

	usb_mode_t usb_mode = Config::usb_mode;

	// Wait a few miliseconds or sometimes it fails to read keys
	sleep_ms(10);

	// Override settings by holding keys on boot
	keys.updateInputState(input_state);
	switch (input_state.keys[0] & 0xB) {
		case 1: // C
			// Reboot to flash mode
			reset_usb_boot(0, PICO_STDIO_USB_RESET_BOOTSEL_INTERFACE_DISABLE_MASK);
			break;
		case 2: // C#
			usb_mode = USB_MODE_MIDI;
			break;
		case 8: // D#
			usb_mode = USB_MODE_KEYBOARD;
			break;
		case 10: // C# and D#
			usb_mode = USB_MODE_DEBUG;
			break;
	}

	usbd_driver_init(usb_mode);

	while (true) {
		keys.updateInputState(input_state);

		usbd_driver_send_report(input_report.getReport(input_state, usb_mode));
		usbd_driver_task();
	}

	return 0;
}
