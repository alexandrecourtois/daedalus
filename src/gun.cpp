#include <gun.h>

Gun::Gun(std::string name, unsigned int ammoMax, unsigned int damage, Sprite* sprite): Nameable(name) {
	m_ammoMax = ammoMax;
	m_ammo = ammoMax;
	m_sprite = sprite;
}

Gun::~Gun()
{
}

