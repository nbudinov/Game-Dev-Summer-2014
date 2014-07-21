#ifndef _SHIPS
#define _SHIPS

#include <SDL.h>
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