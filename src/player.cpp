#include "player.h"

Player::Player() {
	m_health  = 100;
	m_armor = 0; 
}

Player::~Player() {
}

unsigned int Player::getHealth() {
	return m_health;
}

unsigned int Player::getArmor() {
	return m_armor;
}

bool Player::isDead() {
	return m_health == 0;
}
