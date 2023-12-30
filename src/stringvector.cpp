#include <stringvector.h>

StringVector::StringVector() {
}

StringVector::StringVector(const std::string &str, char separator): m_index(0), m_nullStr(NULL_STR) {
	vectorize(str, separator);
}

StringVector::~StringVector() {
}

void StringVector::vectorize(const std::string &str, char separator) {
    m_strVect.clear();

    for (uint i = 0; i < str.size(); i++) {
        int pos = i;

        while (str[i] != separator && i < str.size())
            i++;

        std::string xstr = str.substr(pos, i - pos);

        if (xstr.size())
            m_strVect.push_back(xstr);
    }
}

const std::string &StringVector::getFirstElement() {
	if (m_strVect.size()) {
		m_index = 1;
		return m_strVect[0];
	}
	
	return m_nullStr;
}

const std::string &StringVector::getNextElement() {
	if (m_index && m_index < m_strVect.size())
		return m_strVect[m_index++];
		
	return m_nullStr;
}

const std::string &StringVector::getLastElement() {
	if (m_strVect.size())
		return m_strVect[m_strVect.size() - 1];
		
	return m_nullStr;
}

bool StringVector::isNextElement() {
	return m_index < m_strVect.size();
}

uint StringVector::getSize() {
	return m_strVect.size();
}