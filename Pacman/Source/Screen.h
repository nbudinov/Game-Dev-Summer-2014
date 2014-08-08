#include <SDL.h>
#include <stdio.h>

class Tile;
class LTexture;
class Player;

class Screen
{
public:

	Screen();

	~Screen();

	bool init();

	bool loadMedia();

	bool setTiles( Tile* tiles[] );

	bool setPlayerTex(Player player);

	SDL_Renderer* getRenderer();

private:
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;

};