#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <single.h>
#include <SFML/Graphics.hpp>

#define DEFAULT_FPS		60

class Viewport: public Single<Viewport>, public sf::RenderWindow {
private:
	sf::Vector2f    	m_scaleFactor;
    sf::Clock       	m_clock;
    sf::Time        	m_elapsedTime;
	sf::RectangleShape	m_logo;
    
    float           	m_FPS;
	float					m_FPSTarget;
    
    bool            	m_consoleLock;
	
public:
	Viewport();
	~Viewport();
	
	void init();
	void run();
	
	sf::Vector2f 	getScaleFactor();
    unsigned int 	getFPS();
	float 			getRateFactor();
	float			getElapsedTime();
	
	friend class Console;
};

#define VIEWPORT   Viewport::get()

#endif // VIEWPORT_H
