#include <viewport.h>
#include <hud.h>
#include <string>
#include <iostream>
#include <chrono>
#include <console.h>
#include <resmgr.h>

#define DEFAULT_WIDTH	800
#define DEFAULT_HEIGHT	600

Viewport::Viewport() {
    m_consoleLock = false;
}

Viewport::~Viewport() {
}

void Viewport::run() {
	create(sf::VideoMode(1024, 768), "daedalus");
    setFramerateLimit(60);
	
	m_scaleFactor.x = getSize().x / DEFAULT_WIDTH;
	m_scaleFactor.y = getSize().y / DEFAULT_HEIGHT;

	m_logo.setSize(sf::Vector2f(500.0f, 500.0f));
	m_logo.setTexture(ResMgr::getTexture("LOGO"));
	m_logo.setOrigin(m_logo.getGlobalBounds().width / 2.0f, m_logo.getGlobalBounds().height / 2.0f);
	m_logo.setPosition(sf::Vector2f { this->getSize() / 2u });
   
	while (isOpen())
    {
        // --- calcul du framerate
        m_elapsedTime = m_clock.restart();
        m_FPS = 1000000 / m_elapsedTime.asMicroseconds();
        // ---
        
        sf::Event event;
        while (pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                close();
                
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Key::Escape) {
                    if (!CONSOLE->isActive())
                        CONSOLE->show();
                    else
                        CONSOLE->hide();
 
				
				}
			}
			
			if (event.type == sf::Event::TextEntered) {
				if (CONSOLE->isActive())
					CONSOLE->key(event);
				else {
				}
			}
		}

        clear();
		
		VIEWPORT->draw(m_logo);
        CONSOLE->draw();
		HUD->draw();
		
        display();
	}
}

sf::Vector2f Viewport::getScaleFactor() {
	return m_scaleFactor;
}

unsigned int Viewport::getFPS() {
    return m_FPS;
}

float Viewport::getRateFactor() {
	return m_elapsedTime.asSeconds() * DEFAULT_FPS;
}

