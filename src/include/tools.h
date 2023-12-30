#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <sstream>
#include <regex>

#define NULL_STR		""

typedef unsigned int	uint;
typedef unsigned char	uchar;


class Tools {
private:
	Tools();
	~Tools();
		
public:
	// Strings tools
	template <typename T> static T fromString(const std::string &str) {
		T value;
		std::istringstream stream(str);
		stream >> value;
		return value;
	}
	
	template <typename T> static std::string toString(const T &value) {
		std::ostringstream stream;
		stream << value;
		return stream.str();
	}
	
	static std::string toLowerString(std::string str);
	static std::string toUpperString(std::string str);
	
	static bool isNumber(const std::string &str);
};

#endif // TOOLS_H