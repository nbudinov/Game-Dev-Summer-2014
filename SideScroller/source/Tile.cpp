#include "Tile.h"
#include "ScreenConsts.h"
#include "LTexture.h"

Tile::Tile(int x, int y, int tileType)
{
	box.x = x;
	box.y = y;
	
	box.w = TILE_WIDTH;
	box.h = TILE_HEIGHT;

	type = tileType;
	shown = true;
}

void Tile::show(SDL_Renderer* gRenderer)
{
	tileTex->render(box.x, box.y, gRenderer);	
}

int Tile::getType() 
{
	return type;
}

SDL_Rect Tile::getBox()
{
	return box;
}