#include "Tile.h"
#include "LTexture.h"

Tile::Tile(int x, int y, int tileType)
{
	box.x = x;
	box.y = y;

	box.h = TILE_HEIGHT;
	box.w = TILE_WIDTH;

	type = tileType;
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