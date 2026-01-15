#ifndef UTILS_INPUTSTATE_H_
#define UTILS_INPUTSTATE_H_

#define GLOBALCONFIGURATION_ONLY_CONSTANTS
#include "GlobalConfiguration.h"
#undef GLOBALCONFIGURATION_ONLY_CONSTANTS

#include <array>
#include <cstdint>

namespace Piano2040::Utils {

struct InputState {
public:
	std::array<uint16_t, Piano2040::Config::octave_count> keys{};

	void releaseAll() {
		for (auto &octave : keys) {
			octave = 0;
		}
	}
};

} // namespace Piano2040::Utils

#endif // UTILS_INPUTSTATE_H_
