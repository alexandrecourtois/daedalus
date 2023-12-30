#ifndef STRINGVECTOR_H
#define STRINGVECTOR_H

#include <vector>
#include <string>
#include <tools.h>

class StringVector {
private:
	uint						m_index;
	std::vector<std::string>	m_strVect;
	std::string					m_nullStr;
	
	StringVector();
	
	void vectorize(const std::string &str, char separator);
	
public:
	StringVector(const std::string &str, char separator);
	~StringVector();
	
	const std::string &getFirstElement();
	const std::string &getNextElement();
	const std::string &getLastElement();
	const std::vector<std::string> &getStringVector();
	
	bool isNextElement();
	uint getSize();
};

#endif // STRINGVECTOR_H