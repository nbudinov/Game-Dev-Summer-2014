#include <SDL.h>
#include <stdio.h>

#include "ScreenConsts.h"
#include "Screen.h" 
#include "Tile.h"


Screen scr;

int main(int argc, char *argv[])
{
	Tile *tiles[400];

	scr.init();

	scr.loadMedia();

	if(	scr.setTiles(tiles) == false) {
		printf("set tiles err \n");	
		return -1;
	}

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
		}

		
				SDL_SetRenderDrawColor( scr.getRenderer(), 0xFF, 0x00, 0x00, 0x00 );
				SDL_RenderClear( scr.getRenderer() );

		        // RENDERING
				for(int i = 0; i < 400; i++) {
					//printf( "%d = %d \n ", i, tiles[i]->getType());
					tiles[i]->show(scr.getRenderer());
				}
				
				//SpriteSheetTexture.NewRender(player.playerBox.x, player.playerBox.y, currentClip, gRenderer);

				SDL_RenderPresent( scr.getRenderer() );


	}
	
	
	//system("pause");
	return 0;
}