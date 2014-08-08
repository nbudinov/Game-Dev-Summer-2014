#include <SDL.h>
#include <stdio.h>

#include "ScreenConsts.h"
#include "Screen.h" 
#include "Tile.h"
#include "Player.h"
#include "LTexture.h"
#include "Game.h"

Screen scr;
Game game;

LTexture playerTexture;

bool loadPlayerTex()
{
	playerTexture.loadFromFile( "images/player.png", scr.getRenderer() );

	return true;
}


int main(int argc, char *argv[])
{
	Tile *tiles[400];

	scr.init();

	scr.loadMedia();

	loadPlayerTex();

	if(	scr.setTiles(tiles) == false) {
		printf("set tiles err \n");	
		return -1;
	}

	Player player(32, 32);
	player.setPlayerTex(&playerTexture);

	//scr.setPlayerTex(player);


	bool quit = false;

	SDL_Event e;

	while( !quit )
	{
		while( SDL_PollEvent(&e) != 0 )
		{
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}

			player.handleEvent(e);

		}

		player.update();

		if (game.Collision(player, tiles) == 1 )
		{
			player.playerBox.x += PLAYER_SPEED;
		}
		if (game.Collision(player, tiles) == 2 )
		{
			player.playerBox.x -= PLAYER_SPEED;
		}
		if (game.Collision(player, tiles) == 3 )
		{
			player.playerBox.y += PLAYER_SPEED;
		}
		if (game.Collision(player, tiles) == 4 )
		{
			player.playerBox.y -= PLAYER_SPEED;
		}






			SDL_SetRenderDrawColor( scr.getRenderer(), 0xFF, 0x00, 0x00, 0x00 );
			SDL_RenderClear( scr.getRenderer() );
			
			// RENDERING
			for(int i = 0; i < 400; i++) {
				//printf( "%d = %d \n ", i, tiles[i]->getType());
				tiles[i]->show(scr.getRenderer());
			}
				
			player.render(scr.getRenderer());

			//SpriteSheetTexture.NewRender(player.playerBox.x, player.playerBox.y, currentClip, gRenderer);
			
			SDL_RenderPresent( scr.getRenderer() );

	}
	
	
	//system("pause");
	return 0;
}