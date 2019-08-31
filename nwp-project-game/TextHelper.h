#pragma once

#include <map>

class TextHelper {
public:
	static std::map<std::string, std::string> values;
	static void loadCSV();
};
