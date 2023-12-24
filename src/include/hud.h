#ifndef HUD_H
#define HUD_H

#include <single.h>
#include <drawable.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


class Hud: public Single<Hud>, public Drawable{
private :
    bool        m_showFPS;
    sf::Text    m_fpsText;
    sf::Clock   m_clock;
    
    void drawFPS();
    
public:
	Hud();
	~Hud();
	
    void showFPS();
    void hideFPS();
    
	void draw();
};

#define HUD     Hud::get()

#endif // HUD_H
