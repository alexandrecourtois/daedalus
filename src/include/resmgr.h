#ifndef RESMGR_H
#define RESMGR_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class ResMgr {
private:
    static std::map<std::string, sf::Font*>     m_fonts;
    static std::map<std::string, sf::Texture*>  m_textures;

    ResMgr();
    ~ResMgr();

    static void loadFont(const std::string &fileName, const std::string &id);
    static void loadTexture(const std::string &fileName, const std::string &id);
    
public:
    static void init();

    static sf::Font*    getFont(const std::string &id);
    static sf::Texture* getTexture(const std::string &id);
};

#endif // RESMGR_H