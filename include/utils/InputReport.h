#ifndef UTILS_INPUTREPORT_H_
#define UTILS_INPUTREPORT_H_

#include "utils/InputState.h"

#include "usb/device/hid/keyboard_driver.h"
#include "usb/device/midi_driver.h"
#include "usb/device_driver.h"

#include <cstdint>
#include <string>

namespace Piano2040::Utils {

struct InputReport {
private:
	hid_nkro_keyboard_report_t m_keyboard_report{
		.keycodes = {},
	};
	midi_report_t m_midi_report{
		.keys = {}
	};
	std::string m_debug_report;

	usb_report_t getKeyboardReport(const InputState &state);
	usb_report_t getMidiReport(const InputState &state);
	usb_report_t getDebugReport(const InputState &state);

public:
	InputReport() = default;

	usb_report_t getReport(const InputState &state, usb_mode_t mode);
};

} // namespace Piano2040::Utils

#endif // UTILS_INPUTREPORT_H_