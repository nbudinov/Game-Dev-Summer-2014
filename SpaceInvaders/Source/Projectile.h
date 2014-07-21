#ifndef _PROJECTILE
#define _PROJECTILE

#ifdef _WIN32
#include <SDL.h>
#elif __APPLE__
#include <SDL2/SDL.h>
#endif
#include <string>

#include "GameObject.h"

class LTexture;

class Projectile : public GameObject
{
public:
	//bool alive ;

//	void handleEvent(SDL_Event& e);
    Projectile(int x, int y);

	void update();

	void move();

private:
    static const int VERTICAL_VELOCITY = 1;
};

#endif /*_PROJECTILE */