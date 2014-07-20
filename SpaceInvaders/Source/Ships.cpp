#include "Ships.h"
#include "GameObject.h"


Ships::Ships(int x, int y) : GameObject(x, y)
{
	dead = false;
}

void Ships::update()
{
	if(dir % 2 == 1) 
	{
		mPosX -= shipSpeed;
	}
	else if(dir % 2 == 0) 
	{
		mPosX += shipSpeed;
	}

	if(hitScreenEnd == true)
	{
		mPosY += 30;
	}
}

