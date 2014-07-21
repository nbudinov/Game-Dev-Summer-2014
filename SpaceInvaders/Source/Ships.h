#ifndef _SHIPS
#define _SHIPS


#ifdef _WIN32
#include <SDL.h>
#elif __APPLE__
#include <SDL2/SDL.h>
#endif



#include "GameObject.h"

class Ships : public GameObject
{
public:
	int dir;
	int shipNum;
	bool hitScreenEnd;
	bool shooting;
	
	Ships(int x, int y, int number);

	void update();

	void shoot();
	
protected:
	static const int shipSpeed = 1;
};


#endif /*_SHIPS */