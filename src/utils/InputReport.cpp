#include "utils/InputReport.h"

#include <array>
#include <bitset>
#include <iomanip>
#include <sstream>

namespace Piano2040::Utils {

usb_report_t InputReport::getKeyboardReport(const InputState &state, bool small) {
	m_keyboard_report = {};

	auto set_key = [&](const bool input, const uint8_t keycode) {
		if (input) {
			m_keyboard_report.keycodes[keycode / 8] |= 1 << (keycode % 8);
		}
	};

	std::array<std::array<uint8_t, 13>, Piano2040::Config::octave_count> mappings;
	if(small) {
		mappings = {{
			{},
			{HID_KEY_C, HID_KEY_1, HID_KEY_D, HID_KEY_2, HID_KEY_E, HID_KEY_F, HID_KEY_3, HID_KEY_G, HID_KEY_4, HID_KEY_A, HID_KEY_5, HID_KEY_B},
			{HID_KEY_MINUS}
		}};
	} else {
		mappings = {{
			{HID_KEY_Z, HID_KEY_S, HID_KEY_X, HID_KEY_D, HID_KEY_C, HID_KEY_V, HID_KEY_G, HID_KEY_B, HID_KEY_H, HID_KEY_N, HID_KEY_J, HID_KEY_M, 0},
			{HID_KEY_Q, HID_KEY_2, HID_KEY_W, HID_KEY_3, HID_KEY_E, HID_KEY_R, HID_KEY_5, HID_KEY_T, HID_KEY_6, HID_KEY_Y, HID_KEY_7, HID_KEY_U, 0},
			{HID_KEY_I, HID_KEY_9, HID_KEY_O, HID_KEY_0, HID_KEY_P, HID_KEY_A, HID_KEY_F, HID_KEY_K, HID_KEY_L, HID_KEY_1, HID_KEY_4, HID_KEY_8, HID_KEY_MINUS},
		}};
	}

	for (size_t i = 0; i < state.keys.size(); i++) {
		uint16_t octave = state.keys[i];
		for (size_t j = 0; j < mappings[i].size(); j++) {
			set_key((octave >> j) & 1, mappings[i][j]);
		}
	}

	return {reinterpret_cast<uint8_t *>(&m_keyboard_report), sizeof(hid_nkro_keyboard_report_t)};
}

usb_report_t InputReport::getMidiReport(const InputState &state) {
	for (size_t i = 0; i < state.keys.size(); i++) {
		m_midi_report.keys[i] = state.keys[i];
	}

	return {reinterpret_cast<uint8_t *>(&m_midi_report), sizeof(midi_report_t)};
}

usb_report_t InputReport::getDebugReport(const InputState &state) {
	const auto &octaves = state.keys;

	char out[256] = "Keys: ";
	int chars_written = strlen(out);
	for (uint16_t octave : octaves) {
		for (int key = 0; key < 13; key++) {
			out[chars_written++] = (octave & (1 << key)) ? '1' : '0';
		}

		out[chars_written++] = ' ';
	}
	out[chars_written++] = '\r';
	out[chars_written++] = '\0';
	
	m_debug_report = out;

	return {reinterpret_cast<uint8_t *>(m_debug_report.data()), static_cast<uint16_t>(m_debug_report.size() + 1)};
}

usb_report_t InputReport::getReport(const InputState &state, usb_mode_t mode) {
	switch (mode) {
		case USB_MODE_KEYBOARD:
			return getKeyboardReport(state, false);
		case USB_MODE_KEYBOARD_SMALL:
			return getKeyboardReport(state, true);
		case USB_MODE_MIDI:
			return getMidiReport(state);
		case USB_MODE_DEBUG:
			return getDebugReport(state);
	}

	return getDebugReport(state);
}

} // namespace Piano2040::Utils
