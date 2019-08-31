#include <fstream>
#include <sstream>
#include "TextHelper.h"

std::map<std::string, std::string> TextHelper::values;

void TextHelper::loadCSV() {
	std::string line;
	std::ifstream myfile("assets/strings.csv");
	if (myfile.is_open())
	{
		while (getline(myfile, line, ','))
		{
			std::string key = line;
			if (!getline(myfile, line, ','))
			{
				break;
			}
			else
			{
				std::string value = line;

				std::string charsToTrim = "\n";

				key = key.erase(0, key.find_first_not_of(charsToTrim));
				key = key.erase(key.find_last_not_of(charsToTrim) + 1);

				value = value.erase(0, value.find_first_not_of(charsToTrim));
				value = value.erase(value.find_last_not_of(charsToTrim) + 1);

				values.insert({ key, value });
			}
		}
		myfile.close();
	}
}
