#ifndef CONSOLE_H
#define CONSOLE_H

#include <single.h>
#include <drawable.h>
#include <SFML/Graphics.hpp>
#include <string>

class Console: public Single<Console>, Drawable {
private:
    bool                m_isVisible;
	bool				m_isActive;
	bool				m_isHidden;
    float        		m_speed;
	
    sf::RectangleShape  m_background;
	sf::Text			m_cmdline;
	sf::Text			m_output;
	
	std::string			m_prompt;
	std::string			m_cmd;
	std::string			m_cursor;
	std::string			m_history;
	
	sf::Clock			m_clock;
	
	void expand();
	void retract();
	void execute(const std::string &cmd);

public:
    Console();
    ~Console();
	
	bool isActive();
    
    void show(unsigned int speed = 200);
    void hide();
    void draw();
	void key(const sf::Event &event);
	void write(const std::string &str);
	void writeln(const std::string &str);
};

#define CONSOLE     Console::get()

#endif // CONSOLE_H