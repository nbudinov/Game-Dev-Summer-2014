#ifndef _PLAYER
#define _PLAYER

#ifdef _WIN32
#include <SDL.h>
#elif __APPLE__
#include <SDL2/SDL.h>
#endif

#include "GameObject.h"


typedef enum {
    MovementStand,
    MovementLeft,
    MovementRight,
} Movement;

class Player : public GameObject
{
public:
	//bool alive;
	Player(int x, int y);

	bool handleEvent(SDL_Event& e);

    void update();
private:
    Movement mDirection;

};

#endif /* _PLAYER */