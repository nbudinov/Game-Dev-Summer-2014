#include "Screen.h"

#include "ScreenConsts.h"
#include "LTexture.h"
#include "Tile.h"
#include "Player.h"
#include <fstream>

	LTexture wallTexture;
	LTexture emptyTexture;
	//LTexture playerTexture;

Screen::Screen()
{
	gWindow = NULL;

	gRenderer = NULL;

}

Screen::~Screen()
{
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//IMG_Quit();
	SDL_Quit();
}

bool Screen::init()
{
	
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        printf( "Warning: Linear texture filtering not enabled!" );
    }

    gWindow = SDL_CreateWindow( "PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( gWindow == NULL )
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( gRenderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

    return true;

}

bool Screen::loadMedia()
{
	if( !wallTexture.loadFromFile( "Data/Art/wall.png", gRenderer ) )
	{
		printf(" failed to load wall \n ");
	}

	if( !emptyTexture.loadFromFile( "Data/Art/empty.png", gRenderer ) )
	{
		printf(" failed to load empty \n ");
	}

	//if( !playerTexture.loadFromFile( "images/player.png", gRenderer ) )
	//{
	//	printf(" failed to load player Texture \n ");
	//}


	return true;
}

//bool setPlayerTex( Player pl )
//{
//	pl.setPlayerTex( &playerTexture );
//	return true;
//}

bool Screen::setTiles(Tile* tiles[])
{
	int x = 0, y = 0;

    std::ifstream map( "Data/Levels/map.txt" );

    if( map == NULL )
    {
        return false;
    }

	for( int t = 0; t < 400; t++)
	{
		//printf("IN \n");
		int tileType = -1;

			map >> tileType;

	        if( map.fail() == true )
			{
				map.close();
				printf("failed 1 \n");
			    return false;
			}

			if(tileType >= 0 || tileType < 3) {
				tiles[t] = new Tile( x, y, tileType );
				//printf("x = %d   y = %d   type = %d \n", x, y, tiles[t]->getType());
				if(	tiles[t]->getType() == 0 ) 
				{
					//printf("TUKAAAAA\n");
					tiles[t]->tileTex = &emptyTexture;
				}
				else if(tiles[t]->getType() == 1)
				{
					tiles[t]->tileTex = &wallTexture;				
				}
			}
			else
			{
				printf( "bad TileType \n" );
				return false;
			}

			x += TILE_WIDTH;

			if( x >= SCREEN_WIDTH )
			{
	            x = 0;
	            y += TILE_HEIGHT;
	        }
	    }

    map.close();
	return true;
}



SDL_Renderer* Screen::getRenderer()
{
	return gRenderer;
}
