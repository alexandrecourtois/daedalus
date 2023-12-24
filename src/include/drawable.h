#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <viewport.h>

class Drawable
{
private:
    Viewport* m_viewport;
    
protected:
	Drawable(): m_viewport(VIEWPORT) { }
	~Drawable() { }
    
    Viewport* getViewport() { return m_viewport; }

public:
	virtual void draw() = 0;
};

#endif // DRAWABLE_H
