#include <viewport.h>
#include <hud.h>
#include <string>
#include <iostream>
#include <chrono>
#include <console.h>
#include <resmgr.h>
#include <player.h>
#include <rc_engine.h>
#include <dataref.h>

#define DEFAULT_WIDTH	800
#define DEFAULT_HEIGHT	600

Viewport::Viewport() {
    m_consoleLock = false;
	//Dataref::set("fps_lock", Dataref::AccessType::rw, 60);
}

Viewport::~Viewport() {
}

void Viewport::run() {
	create(sf::VideoMode(1024, 768), "daedalus");
    //setFramerateLimit(Dataref::get<int>("fps_lock"));
	
	m_scaleFactor.x = getSize().x / DEFAULT_WIDTH;
	m_scaleFactor.y = getSize().y / DEFAULT_HEIGHT;

	m_logo.setSize(sf::Vector2f(500.0f, 500.0f));
	m_logo.setTexture(ResMgr::getTexture("LOGO"));
	m_logo.setOrigin(m_logo.getGlobalBounds().width / 2.0f, m_logo.getGlobalBounds().height / 2.0f);
	m_logo.setPosition(sf::Vector2f { this->getSize() / 2u });

	Player p;
	RC_engine e;
	e.init(&p);
	
	int prevMouseX = sf::Mouse::getPosition().x;
	int currMouseX = prevMouseX;

	while (isOpen())
    {
        // --- calcul du framerate
        m_elapsedTime = m_clock.restart();
        m_FPS = 1000000 / m_elapsedTime.asMicroseconds();
        // ---
		
		//std::cout << m_elapsedTime.asSeconds() << "\n";
        
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
		
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					e.moveForward();
				}
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					e.moveBackward();
				}
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
					e.rotateLeft();
				}
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					e.rotateRight();
				}
/*
		currMouseX = sf::Mouse::getPosition().x;

		if (currMouseX < prevMouseX) {
			e.rotateLeft();
		}
		
		if (currMouseX > prevMouseX) {
			e.rotateRight();
		}
		
		prevMouseX = 500;
		sf::Mouse::setPosition(sf::Vector2i(500, 500));
*/
        clear();
		
		VIEWPORT->draw(m_logo);
		e.render();
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

float Viewport::getElapsedTime() {
	return m_elapsedTime.asSeconds();
}

