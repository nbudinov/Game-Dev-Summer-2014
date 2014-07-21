#include "Ships.h"
#include "GameObject.h"
#include <ScreenConsts.h>

Ships::Ships(int x, int y, int number) : GameObject(x, y)
{
	shooting = false;
	shipNum = number;
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
	//if(mPosY < SCREEN_HEIGHT - 100) {
		if(hitScreenEnd == true)
		{
			mPosY += 10;
		}
	//}
}

void Ships::shoot()
{
	shooting = true;
}