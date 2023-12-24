#include <console.h>
#include <iostream>
#include <resmgr.h>
#include <viewport.h>
#include <algorithm>

Console::Console() {
    m_isVisible = false;
	m_isActive 	= false;
	m_isHidden	= true;
    m_speed 	= 2;
	
    m_background.setSize(sf::Vector2f(VIEWPORT->getSize().x, VIEWPORT->getSize().y * 0.8));
    //m_background.setTexture(ResMgr::getTexture("CONSOLE_BG"));
	m_background.setFillColor(sf::Color(100, 50, 50, 127));
    m_background.setPosition(0, -m_background.getSize().y);
	
	m_cmdline = sf::Text { "]", *ResMgr::getFont("RMR") };
	m_cmdline.setOrigin(m_cmdline.getLocalBounds().left, m_cmdline.getLocalBounds().top);
	
	m_output = sf::Text { "", *ResMgr::getFont("RMR") };
	m_output.setOrigin(m_output.getLocalBounds().left, m_output.getLocalBounds().top);
	

	m_prompt 	= "]";
	m_cursor 	= "_";
	m_cmd		= "";
	m_history	= "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nDAEDALUS CMD";
	
	m_output.setString(m_history);
}

Console::~Console() {
}

void Console::show(unsigned int speed) {
    m_isVisible = true;
    m_speed 	= m_background.getSize().y * (1000.0f / speed) / DEFAULT_FPS;
}

void Console::hide() {
    m_isVisible = false;
}

void Console::expand() {
	if (m_background.getPosition().y < 0) {
		float ypos_bg 		= m_background.getPosition().y + m_speed * VIEWPORT->getRateFactor();
			
		if (ypos_bg > 0) {
			ypos_bg		= 0;
			m_isActive	= true;
		}

		float ypos_prompt	= ypos_bg + m_background.getSize().y - m_cmdline.getLocalBounds().height - 10;

		m_background.setPosition(0, ypos_bg);
		m_cmdline.setPosition(10, ypos_prompt);
		m_output.setPosition(10, ypos_bg);
		//m_cursor.setPosition(m_cmdline.getPosition().x + m_cmdline.getLocalBounds().width, ypos_prompt);
		m_isHidden = false;
	}
}

void Console::retract() {
	if (m_background.getPosition().y > -m_background.getSize().y) {
		float ypos_bg = m_background.getPosition().y - m_speed * VIEWPORT->getRateFactor();
		
		m_isActive 	= false;	
		
		if (ypos_bg < -m_background.getSize().y) {
			ypos_bg = -m_background.getSize().y;
			m_isHidden = true;
		}
		
		float ypos_prompt	= ypos_bg + m_background.getSize().y - m_cmdline.getLocalBounds().height - 10;

		m_background.setPosition(0, ypos_bg);
		m_cmdline.setPosition(10, ypos_prompt);
		m_output.setPosition(10, ypos_bg);
	}
}

void Console::draw() {
    if (m_isVisible)
		expand();
	else
		retract();			
	
	if (!m_isHidden) {
		VIEWPORT->draw(m_background);
		VIEWPORT->draw(m_cmdline);
		VIEWPORT->draw(m_output);
		
		if (m_clock.getElapsedTime().asMilliseconds() <= 500) {
			m_cmdline.setString(m_prompt + m_cmd + m_cursor);
		} else
			if (m_clock.getElapsedTime().asMilliseconds() <= 1000) {
				m_cmdline.setString(m_prompt + m_cmd);
			} else
				m_clock.restart();
			
	}
}

bool Console::isActive() {
	return m_isActive;
}

void Console::key(const sf::Event &event) {
	if (event.type == sf::Event::TextEntered)
		switch(event.text.unicode) {
			case 8:												// BACKSPACE
				m_cmd = m_cmd.substr(0, m_cmd.size() - 1);
				break;
				
			case 13:											// RETURN
				execute(m_cmd);
				m_cmd = "";
				break;
				
			case 27:											// ESCAPE
				break;
				
			default:
				m_cmd += static_cast<char>(event.text.unicode);
		}
/*		
		if (event.text.unicode < 128) {
			if (event.text.unicode == 8)	// BACKSPACE
				m_cmd = m_cmd.substr(0, m_cmd.size() - 1);
			else
				m_cmd += static_cast<char>(event.text.unicode);
		}*/
}

void Console::execute(const std::string &cmd) {
	if (cmd != "") {
		if (cmd == "clear") {
			m_history	= "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
			m_output.setString(m_history);
			
			return;
		}
		
		if (cmd == "exit") {
			VIEWPORT->close();
			
			return;
		}
		
		writeln("Unknown command: " + cmd);
	}
}

void Console::write(const std::string &str) {
	m_history += str;
}

void Console::writeln(const std::string &str) {
	write("\n" + str);
	
	int eol = 0;
	int eolnum = std::count(m_history.begin(), m_history.end(), '\n');
	int i 	= 0;
	
	while(eol < eolnum - 14) {
		if (m_history[i] == '\n')
			eol++;
			
		i++;
	}
	
	m_history = m_history.substr(i - 1, m_history.size() - 1);
	m_output.setString(m_history);
}