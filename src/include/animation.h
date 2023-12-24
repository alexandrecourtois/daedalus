#ifndef ANIMATION_H
#define ANIMATION_H

#include <spritesheet.h>

class Animation {
private:
    SpriteSheet* m_spriteSheet;
    
public:
    Animation(SpriteSheet* spriteSheet);
    ~Animation();
    
    void run();
    void runOnce();
    void off();
    
};

#endif // ANIMATION_H