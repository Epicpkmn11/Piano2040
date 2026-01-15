#ifndef PERIPHERALS_KEYS_H_
#define PERIPHERALS_KEYS_H_

#include "utils/InputState.h"

#include <array>
#include <cstdint>
#include <vector>

namespace Piano2040::Peripherals {

class Keys {
public:
	struct Config {
		struct {
			std::array<uint8_t, 13> keys;
			std::array<uint8_t, Piano2040::Config::octave_count> octaves;
		} pins;

		uint8_t debounce_delay_ms;
	};

private:
	class Key {
	private:
		uint8_t m_gpio_pin;
		uint32_t m_gpio_mask;

		uint32_t m_last_change{0};
		bool m_active{false};

	public:
		Key(uint8_t pin);

		[[nodiscard]] uint8_t getGpioPin() const { return m_gpio_pin; };
		[[nodiscard]] uint32_t getGpioMask() const { return m_gpio_mask; };

		[[nodiscard]] bool getState() const { return m_active; };
		void setState(bool state, uint8_t debounce_delay);
	};

	Config m_config;
	std::vector<Key> m_keys;

public:
	Keys(const Config &config);

	void updateInputState(Utils::InputState &input_state);
};

} // namespace Piano2040::Peripherals

#define PERIPHERALS_KEYS_H_LOADED
#endif // PERIPHERALS_KEYS_H_
