#ifndef _PROJECTILE
#define _PROJECTILE

//#ifdef WIN32
#include <SDL.h>
//#elif __APPLE__
//#include <SDL2/SDL.h>
//#endif
#include <string>

#include "GameObject.h"

class LTexture;

class Projectile : public GameObject
{
public:
//	void handleEvent(SDL_Event& e);
    Projectile(int x, int y);

	void update();
private:
    static const int VERTICAL_VELOCITY = 1;
};

#endif /*_PROJECTILE */