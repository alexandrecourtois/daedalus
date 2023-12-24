#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>
#include <vector>

class Sprite {
private:
	std::vector<sf::Texture*> m_images;
	
protected:
	Sprite();
	~Sprite();

public:
	void addImage(sf::Texture* texture);
	void draw();
};

#endif // SPRITE_H
