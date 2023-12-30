#include <console.h>
#include <iostream>
#include <resmgr.h>
#include <viewport.h>
#include <algorithm>
#include <math.h>
#include <tools.h>
#include <stringvector.h>
#include <dataref.h>
#include <AnimatedGIF.h>

Console::Console() {
    m_isVisible = false;
	m_isActive 	= false;
	m_isHidden	= true;
    m_speed 	= 2;
	m_fontSize	= 24;
	m_isInit	= false;
	m_historyChanged = false;
	m_JPmode = false;
	m_ahahah = false;
	m_fatboy = AnimatedGIF("res/magicword.gif");
	m_tetaclaq.loadFromFile("res/magicword.wav");
	m_youdidntsaythemagicword.setBuffer(m_tetaclaq);
	m_youdidntsaythemagicword.setLoop(true);
	
	m_outputLines = (24 / m_fontSize) * 19;
		

	m_prompt 	= "]";
	m_cursor 	= "_";
	m_cmd		= "";
	
	for(unsigned int i = 0; i < m_outputLines; ++i)
		m_history += '\n';
		
	m_history += "DEADALUS CMD";
}

Console::~Console() {
}

void Console::initFonts() {
    m_background.setSize(sf::Vector2f(VIEWPORT->getSize().x, VIEWPORT->getSize().y * 0.8));
	m_background.setFillColor(sf::Color(0, 0, 0, 200));
    m_background.setPosition(0, -m_background.getSize().y);
	
	m_cmdline = sf::Text { "]", *ResMgr::getFont("MSDOS") };
	m_cmdline.setCharacterSize(m_fontSize);
	m_cmdline.setOrigin(m_cmdline.getLocalBounds().left, m_cmdline.getLocalBounds().top);
	
	m_output = sf::Text { "", *ResMgr::getFont("MSDOS") };
	m_output.setCharacterSize(m_fontSize);
	m_output.setOrigin(m_output.getLocalBounds().left, m_output.getLocalBounds().top);
	
	m_isInit = true;
}

void Console::resetOutput() {
	m_history = "";
	
	for(unsigned int i = 0; i < m_outputLines; ++i)
		m_history += '\n';
	
	if (!m_JPmode)
		m_history += "DEADALUS CMD";
	//else
	//	m_history = "";
		
	m_output.setString(m_history);
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
		m_output.setPosition(10, ypos_prompt - m_output.getLocalBounds().height - m_cmdline.getLocalBounds().height - 10);
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
		m_output.setPosition(10, ypos_prompt - m_output.getLocalBounds().height - m_cmdline.getLocalBounds().height - 10);
	}
}

void Console::draw() {
	if (!m_isInit)
		initFonts();
	
    if (m_isVisible)
		expand();
	else
		retract();			
	
	if (!m_isHidden) {
		if (m_historyChanged) {
			m_output.setString(m_history);
			m_historyChanged = false;
		}
		
		VIEWPORT->draw(m_background);
		VIEWPORT->draw(m_cmdline);
		VIEWPORT->draw(m_output);
		
		if (m_ahahah) {
			m_fatboy.update(m_nedry);
			m_nedry.setPosition(VIEWPORT->getSize().x - m_fatboy.getSize().x, 0);
			VIEWPORT->draw(m_nedry);
		}
		
		if (m_clock.getElapsedTime().asMilliseconds() <= 500) {
			m_cmdline.setString(m_prompt + m_cmd + m_cursor);
			//m_output.setString(m_history + "\n" + m_prompt + m_cmd + m_cursor); /////// !!!!!!!
		} else
			if (m_clock.getElapsedTime().asMilliseconds() <= 1000) {
				m_cmdline.setString(m_prompt + m_cmd);
				//m_output.setString(m_history + "\n" + m_prompt + m_cmd); ////// !!!!!!!
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
}

void Console::execute(std::string cmd_line) {
	StringVector argList = StringVector(/*Tools::toLowerString(*/cmd_line/*)*/, ' ');
	std::string	cmd = argList.getFirstElement();
	std::string arg1, arg2, arg3;
	
	if (cmd != NULL_STR) {
		if (cmd == "clear") {
			if (argList.getSize() == 1)
				resetOutput();
			else
				CONSOLE->writeln("Usage: clear");
				
			return;
		}
		
		if (cmd == "exit") {
			if (argList.getSize() == 1)
				VIEWPORT->close();
			else
				CONSOLE->writeln("Usage: exit");
				
			return;
		}
		
		if (cmd == "set") {
			if (argList.getSize() == 3) {
				arg1 = argList.getNextElement();
				arg2 = argList.getNextElement();
				
				if (arg1 == "fps") {
					if (Tools::isNumber(arg2)) {
						VIEWPORT->setFramerateLimit(Tools::fromString<int>(arg2));
						CONSOLE->writeln("FPS set at " + arg2);
					}
					else
						CONSOLE->writeln("set: invalid argument " + arg2);
				} else
					Dataref::set(arg1, arg2);
			} else
				CONSOLE->writeln("Usage: set param value");
				
			return;
		}
		
		if (cmd == "get") {
			if (argList.getSize() > 1)
				while(argList.isNextElement())
					//arg1 = argList.getNextElement();
					Dataref::get(argList.getNextElement());
			else
				CONSOLE->writeln("Usage: get param1 param2...");
			
			return;
		}
		
		if (cmd == "jp_on" && !m_JPmode) {
			m_JPmode = true;
			m_prompt = ">";
			m_background.setFillColor(sf::Color(0, 0, 255, 255));
			resetOutput();
						
			
			
			CONSOLE->writeln("Jurassic Park, System Security Interface");
			CONSOLE->writeln("Version 4.0.5, Alpha E");
			CONSOLE->writeln("Ready...");
			
			return;
		}
		
		if (cmd == "jp_off" && m_JPmode) {
			m_JPmode = false;
			m_ahahah = false;
			m_youdidntsaythemagicword.stop();
			m_prompt = "]";
			m_background.setFillColor(sf::Color(0, 0, 0, 200));
			resetOutput();
			
			return;
		}
		
		if (m_JPmode) {
			CONSOLE->writeln(m_prompt + cmd_line);
			
			if (cmd == "access") {
				if (argList.getSize() == 4) {
					arg1 = argList.getNextElement();
					arg2 = argList.getNextElement();
					arg3 = argList.getNextElement();
					
					if (arg1 == "main" && arg2 == "security" && arg3 == "grid") {
						m_ahahah = true;
						CONSOLE->writeln("access: PERMISSION DENIED....and...");
						CONSOLE->writeln("YOU DIDN'T SAY THE MAGIC WORD!");
						CONSOLE->writeln("YOU DIDN'T SAY THE MAGIC WORD!");
						CONSOLE->writeln("YOU DIDN'T SAY THE MAGIC WORD!");
						CONSOLE->writeln("YOU DIDN'T SAY THE MAGIC WORD!");
						CONSOLE->writeln("YOU DIDN'T SAY THE MAGIC WORD!");
						CONSOLE->writeln("YOU DIDN'T SAY THE MAGIC WORD!");
						CONSOLE->writeln("YOU DIDN'T SAY THE MAGIC WORD!");
						CONSOLE->writeln("YOU DIDN'T SAY THE MAGIC WORD!");
						CONSOLE->writeln("YOU DIDN'T SAY THE MAGIC WORD!");
						m_youdidntsaythemagicword.play();
						
						return;
					}
				}
			}
				
				CONSOLE->writeln("access: PERMISSION DENIED.");
				
				return;
		}
		
		CONSOLE->writeln(cmd + ": unknown command");
	}
}

void Console::write(const std::string &str) {
	m_history += str;
	m_historyChanged = true;
}

void Console::writeln(const std::string &str) {
	std::cout << str << "\n";
	
	write("\n" + str);
	
	int eol = 0;
	int eolnum = std::count(m_history.begin(), m_history.end(), '\n');
	int i 	= 0;
	
	while(eol < eolnum - m_outputLines + 1) {
		if (m_history[i] == '\n')
			eol++;
			
		i++;
	}
	
	m_history = m_history.substr(i - 1, m_history.size() - 1);
}