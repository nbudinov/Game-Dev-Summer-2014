#include <SDL.h>
#include "ScreenConsts.h"

class LTexture;

class Tile
{
public:
	bool shown;

	LTexture *tileTex;

	Tile( int x, int y, int tileType );

	void show(SDL_Renderer* gRenderer);

	int getType();

	SDL_Rect getBox();

private:
	SDL_Rect box;
	int type;
	
};