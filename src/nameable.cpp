#include <nameable.h>

Nameable::Nameable() {
}

Nameable::Nameable(std::string name) {
	m_name = name;
}

Nameable::~Nameable()
{
}

void Nameable::setName(std::string name) {
	m_name = name;
}

std::string Nameable::getName() {
	return m_name;
}
