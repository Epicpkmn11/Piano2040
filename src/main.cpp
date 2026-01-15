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

	usbd_driver_init(Config::usb_mode);

	// Enter flash mode if plugged in while holding the leftmost key
	keys.updateInputState(input_state);
	if (input_state.keys[0] & 1)
		reset_usb_boot(0, PICO_STDIO_USB_RESET_BOOTSEL_INTERFACE_DISABLE_MASK);

	while (true) {
		keys.updateInputState(input_state);

		usbd_driver_send_report(input_report.getReport(input_state, Piano2040::Config::usb_mode));
		usbd_driver_task();
	}

	return 0;
}
