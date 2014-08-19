
#include "Mobs.h"
#include "LTexture.h"
#include "ScreenConsts.h"
Mobs::Mobs(int x, int y, int type)
{
	//mobX = x;
	//mobY = y;
	mobType = type;

	mobBox.x = x;
	mobBox.y = y;

	mobBox.w = TILE_WIDTH;
	mobBox.h = TILE_HEIGHT;
	
	mobDir = MoveRight;
}


SDL_Rect Mobs::getMobBox()
{
	return mobBox;
}

void Mobs::render(SDL_Renderer* gRenderer)
{
	mobTexture->NewRender(mobBox.x, mobBox.y, NULL, gRenderer);
}