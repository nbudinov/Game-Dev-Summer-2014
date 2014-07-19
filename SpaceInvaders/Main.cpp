#include <iostream>

#include "ScreenConsts.h"

#include "Player.h"
#include "Projectile.h" 
#include "LTexture.h"

#ifdef WIN32
#include <SDL.h>
#include <SDL_image.h>
#elif __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif
#include <vector>
#include <list>

using namespace std;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

LTexture gPlayerTexture;
LTexture gProjTexture;

bool init()
{
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        return false;
	}

    //Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        printf( "Warning: Linear texture filtering not enabled!" );
    }

    //Create window
    gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( gWindow == NULL )
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    //Create vsynced renderer for window
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( gRenderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    //Initialize renderer color
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return false;
    }

    return true;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if( !gPlayerTexture.loadFromFile( "Textures/dot.bmp", gRenderer ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	if( !gProjTexture.loadFromFile( "Textures/dot.bmp", gRenderer ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	return success;
}

void close()
	{
		gPlayerTexture.free();

		SDL_DestroyRenderer( gRenderer );
		SDL_DestroyWindow( gWindow );
		gWindow = NULL;
		gRenderer = NULL;

		//IMG_Quit();
		SDL_Quit();
	}


std::list<Projectile*> Projects;

std::list<GameObject*> gameObjects;

void addProj(Player pl)
{
	int x = pl.getPosX();
	Projectile * tmp = new Projectile(x, SCREEN_HEIGHT - gProjTexture.getHeight()*2);
    tmp->setTex(&gProjTexture);
	Projects.push_back(tmp);
    gameObjects.push_back(tmp);
}

	

int main( int argc, char* args[])
 {
	
//	 int i = 0;


	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			bool quit = false;

			SDL_Event e;

			Player player(0, SCREEN_HEIGHT - gPlayerTexture.getHeight());
            player.setTex(&gPlayerTexture);
            gameObjects.push_back(&player);
        
			while( !quit )
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					bool shouldShoot = player.handleEvent( e );
                    if (shouldShoot)
                        addProj(player);
				}
                
                for(std::list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end();)
                {
                    (*it)->update();
                    ++it;
                }

                // RENDERING
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

                
                for(std::list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end();)
                {
                    (*it)->render(gRenderer);
                    ++it;
                }
				
				SDL_RenderPresent( gRenderer );
			}
		}
	
	}
	close();

	return 0;
}
