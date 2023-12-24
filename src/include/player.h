#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>
#include <gun.h>
#include <nameable.h>
#include <single.h>

class Player: public Single<Player>, public Nameable {
private:
	unsigned int	m_health;
	unsigned int	m_armor;
	
	Gun*							m_gun;
	std::map<std::string, Gun*>		m_armory;
	
public:
	Player();
	~Player();
	
	unsigned int	getHealth();
	unsigned int	getArmor();
	
	bool			isDead();
};

#endif // PLAYER_H
