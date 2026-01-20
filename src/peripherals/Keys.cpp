#include "peripherals/Keys.h"

#include "hardware/gpio.h"
#include "pico/time.h"

namespace Piano2040::Peripherals {

Keys::Key::Key(uint8_t pin) : m_gpio_pin(pin), m_gpio_mask(1 << pin) {}

void Keys::Key::setState(bool state, uint8_t debounce_delay) {
	if (m_active == state) {
		return;
	}

	// Immediately change the input state, but only allow a change every debounce_delay milliseconds.
	if (state) {
		m_active = true;
		m_last_state = true;
	} else {
		const uint32_t now = to_ms_since_boot(get_absolute_time());
		if (m_last_state) {
			m_last_state = false;
			m_last_change = now;
		} else if (m_last_change + debounce_delay <= now) {
			m_active = false;
		}
	}
}

Keys::Keys(const Config &config) : m_config(config) {
	for (int octave = 0; octave < Piano2040::Config::octave_count; octave++) {
		for (uint8_t key : config.pins.keys) {
			m_keys[octave].emplace_back(key);
		}

		for (const auto &key : m_keys[octave]) {
			gpio_init(key.getGpioPin());
			gpio_set_dir(key.getGpioPin(), GPIO_IN);
			gpio_pull_down(key.getGpioPin());
		}
	}

	for (auto pin : config.pins.octaves) {
		gpio_init(pin);
		gpio_set_dir(pin, GPIO_OUT);
	}
}

void Keys::updateInputState(Utils::InputState &input_state) {
	for (size_t i = 0; i < Piano2040::Config::octave_count; i++) {
		gpio_put(m_config.pins.octaves[i], 1);
		sleep_us(Piano2040::Config::sleep_us);
		const uint32_t gpio_state = gpio_get_all();
		gpio_put(m_config.pins.octaves[i], 0);
		
		uint16_t &octave = input_state.keys[i];
		octave = 0;
		for (size_t j = 0; j < m_keys[i].size(); j++) {
			Key &key = m_keys[i][j];
			key.setState(gpio_state & key.getGpioMask(), m_config.debounce_delay_ms);
			octave |= key.getState() << j;
		}
	}
}

} // namespace Piano2040::Peripherals
