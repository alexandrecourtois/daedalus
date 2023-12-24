#include <nameable.h>

Nameable::Nameable() {
}

Nameable::Nameable(std::string name) {
	name = name;
}

Nameable::~Nameable()
{
}

void Nameable::setName(std::string name) {
	name = name;
}

std::string Nameable::getName() {
	return name;
}
