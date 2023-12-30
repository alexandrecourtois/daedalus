#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>
#include <gun.h>
#include <nameable.h>
#include <single.h>
#include <tools.h>

class Player: public Single<Player>, public Nameable {
private:
	int*							m_health;
	int*							m_armor;
	Gun*							m_gun;
	std::map<std::string, Gun*>		m_armory;
	
	sf::Vector2f					m_position;
	sf::Vector2f					m_direction;
	float*							m_moveSpeed;
	float*							m_rotationSpeed;
	float*							m_box;
	sf::Vector2f					m_box2d;
	sf::Vector2f					m_plane;
	
	void updateName();
	
public:
	Player();
	~Player();
	
	uint			getHealth();
	uint			getArmor();
	
	bool			isDead();
	
	sf::Vector2f	getPosition();
	sf::Vector2f	getDirection();
	sf::Vector2f	getPlane();
	float			getMoveSpeed();
	sf::Vector2f	getBox2D();
	float			getRotateSpeed();
	
	void			setPlane(float x, float y);
	void			setPosition(float x, float y);
	void			setDirection(float x, float y);
	
	friend class Console;
};

#endif // PLAYER_H
