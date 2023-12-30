#include <tools.h>
#include <algorithm>

std::string Tools::toLowerString(std::string str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

std::string Tools::toUpperString(std::string str) {
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	return str;
}

bool Tools::isNumber(const std::string &str) {
	std::regex numRegex("^[-+]?([0-9]*\\.[0-9]+|[0-9]+)$");
	return std::regex_match(str, numRegex);
}