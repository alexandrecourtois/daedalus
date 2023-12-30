#ifndef NAMEABLE_H
#define NAMEABLE_H

#include <string>

class Nameable {
private:
	std::string m_name;
	
protected:
	Nameable();
	Nameable(std::string name);	
	~Nameable();
	
public:
	void		setName(std::string name);
	std::string	getName();
};

#endif // NAMEABLE_H
