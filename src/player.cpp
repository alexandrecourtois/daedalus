#include <player.h>
#include <dataref.h>

Player::Player() {
	newData_s("p_name",		RW, std::string("LtC_Kilgore"), updateCode{updateName();});
	
	newData_f("p_mSpeed", 	RW, 5.0f, 	&m_moveSpeed);
	newData_f("p_rSpeed", 	RW, 10.0f, 	&m_rotationSpeed);
	newData_f("p_boxSize", 	RW, 0.375f, &m_box);
	
	newData_i("p_health", 	RW, 100, 	&m_health);
	newData_i("p_armor", 	RW, 0,		&m_armor);
	
	m_position 		= sf::Vector2f(2.5f, 2.0f);
	m_direction 	= sf::Vector2f(0.0f, 1.0f);
	m_box2d			= sf::Vector2f(*m_box, *m_box);
	m_plane			= sf::Vector2f(-0.66f, 0.0f);
}

Player::~Player() {
}

void Player::updateName() {
	setName(Dataref::get("p_name"));
	std::cout << "pname:"+getName() << "\n";
}

unsigned int Player::getHealth() {
	return *m_health;
}

unsigned int Player::getArmor() {
	return *m_armor;
}

bool Player::isDead() {
	return *m_health == 0;
}

sf::Vector2f Player::getPosition() {
	return m_position;
}

sf::Vector2f Player::getDirection() {
	return m_direction;
}

sf::Vector2f Player::getPlane() {
	return m_plane;
}

void Player::setPosition(float x, float y) {
	m_position.x = x;
	m_position.y = y;
}

void Player::setDirection(float x, float y) {
	m_direction.x = x;
	m_direction.y = y;
}

float Player::getMoveSpeed() {
	return *m_moveSpeed;
}

sf::Vector2f Player::getBox2D() {
	return m_box2d;
}

float Player::getRotateSpeed() {
	return *m_rotationSpeed;
}

void Player::setPlane(float x, float y) {
	m_plane.x = x;
	m_plane.y = y;
}