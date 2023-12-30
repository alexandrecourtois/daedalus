#ifndef CONSOLE_H
#define CONSOLE_H

#include <single.h>
#include <drawable.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <iostream>
#include <AnimatedGIF.h>
#include <SFML/Audio.hpp>

class Console: public Single<Console>, Drawable {
private:
    bool                m_isVisible;
	bool				m_isActive;
	bool				m_isHidden;
	bool				m_isInit;
	bool				m_historyChanged;
    float        		m_speed;
	bool				m_JPmode;
	bool				m_ahahah;
	
	sf::SoundBuffer		m_tetaclaq;
	sf::Sound			m_youdidntsaythemagicword;
    sf::RectangleShape  m_background;
	sf::Text			m_cmdline;
	sf::Text			m_output;
	sf::Sprite			m_nedry;
	
	AnimatedGIF			m_fatboy;
	
	std::string			m_prompt;
	std::string			m_cmd;
	std::string			m_cursor;
	std::string			m_history;
	
	sf::Clock			m_clock;
	
	unsigned int		m_outputLines;
	unsigned int		m_fontSize;
	
	void initFonts();
	void expand();
	void retract();
	void execute(std::string cmd);
	void resetOutput();

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