#include <hud.h>
#include <iostream>
#include <player.h>
#include <viewport.h>
#include <string>
#include <resmgr.h>

Hud::Hud() {
    m_showFPS = true;
    m_fpsText.setFont(*ResMgr::getFont("MSDOS"));
    //m_fpsText.setScale(0.8, 0.8);
	//m_fpsText.setPosition(10.0f, 10.0f);
}

Hud::~Hud() {
}

void Hud::showFPS() {
    m_showFPS = true;
}

void Hud::hideFPS() {
    m_showFPS = false;
}

void Hud::draw() {
    if (m_showFPS)
        drawFPS();
}

void Hud::drawFPS() {
    if (m_clock.getElapsedTime().asMilliseconds() > 500) {
        m_fpsText.setString("FPS " + std::to_string(getViewport()->getFPS()));
        m_clock.restart();
    }

    getViewport()->draw(m_fpsText);
}

