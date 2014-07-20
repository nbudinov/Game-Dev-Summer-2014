#include "Projectile.h"
#include "ScreenConsts.h"
#include "LTexture.h"
#include "GameObject.h"

#include <iostream>

Projectile::Projectile(int x, int y)
    : GameObject(x, y)
{}

void Projectile::update()
{
    mPosY -= VERTICAL_VELOCITY;
}

void Projectile::move()
{
	mPosY += VERTICAL_VELOCITY;
}
