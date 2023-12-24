#ifndef GUN_H
#define GUN_H

#include <SFML/Graphics.hpp>
#include <sprite.h>
#include <string>
#include <nameable.h>

class Gun: public Nameable {
private:
	unsigned int	m_ammoMax;
	unsigned int	m_ammo;
	unsigned int	m_damage;

	Sprite*			m_sprite;
	
protected:
	Gun(std::string name, unsigned int ammoMax, unsigned int damage, Sprite* sprite);
	
public:
	~Gun();
};

#endif // GUN_H
