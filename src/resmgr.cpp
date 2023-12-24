#include <resmgr.h>

std::map<std::string, sf::Font*> ResMgr::m_fonts = std::map<std::string, sf::Font*>();
std::map<std::string, sf::Texture*> ResMgr::m_textures = std::map<std::string, sf::Texture*>();

ResMgr::ResMgr() {
}

ResMgr::~ResMgr() {
}

void ResMgr::loadFont(const std::string &filename, const std::string &id) {
    sf::Font* f = new sf::Font();
    
    if (f->loadFromFile(filename))
        ResMgr::m_fonts[id] = f;
    else
        delete f;
}

void ResMgr::loadTexture(const std::string &filename, const std::string &id) {
    sf::Texture* t = new sf::Texture();
    
    if (t->loadFromFile(filename))
        ResMgr::m_textures[id] = t;
    else
        delete t;
}

void ResMgr::init() {
    ResMgr::loadFont("res/DooM.ttf", "DOOM");
	ResMgr::loadFont("res/PixeloidMono.ttf", "PIX_MONO");
	ResMgr::loadFont("res/roboto_mono_regular.ttf", "RMR");
	
    ResMgr::loadTexture("res/marble.jpg", "CONSOLE_BG");
	ResMgr::loadTexture("res/logo.jpg", "LOGO");
}

sf::Font* ResMgr::getFont(const std::string &id) {
    auto item = ResMgr::m_fonts.find(id);
    
    if (item != ResMgr::m_fonts.end())
        return item->second;
        
    return nullptr;
}

sf::Texture* ResMgr::getTexture(const std::string &id) {
    auto item = ResMgr::m_textures.find(id);
    
    if (item != ResMgr::m_textures.end())
        return item->second;
        
    return nullptr;
}