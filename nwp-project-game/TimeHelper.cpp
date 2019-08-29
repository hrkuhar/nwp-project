#include "TimeHelper.h"

std::string TimeHelper::millisToString(uint32_t millis) {
	uint32_t minutes;
	uint32_t seconds;

	minutes = millis / 60000;
	uint32_t remainder = millis % 60000;

	seconds = remainder / 1000;

	std::string minutesStr = minutes <= 9 ? "0" + std::to_string(minutes) : std::to_string(minutes);
	std::string secondsStr = seconds <= 9 ? "0" + std::to_string(seconds) : std::to_string(seconds);

	return minutesStr + ":" + secondsStr;
}