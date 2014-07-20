#ifndef _SHIPS
#define _SHIPS

#include <SDL.h>
#include "GameObject.h"

class Ships : public GameObject
{
public:
	int dir;
	bool hitScreenEnd;
	bool dead;

	Ships(int x, int y);

	void update();

	void shoot();
	
protected:
	static const int shipSpeed = 1;
};


#endif /*_SHIPS */