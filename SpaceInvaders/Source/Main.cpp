#include <iostream>

#include "ScreenConsts.h"
#include <GameObject.h>
#include "Player.h"
#include "Projectile.h" 
#include "LTexture.h"
#include "Ships.h"

//#ifdef WIN32
#include <SDL.h>
#include <SDL_image.h>
//#elif __APPLE__
//#include <SDL2/SDL.h>
//#include <SDL2_image/SDL_image.h>
//#endif
#include <vector>
#include <list>

using namespace std;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

LTexture gPlayerTexture;
LTexture gProjTexture;
LTexture gShipTexture;

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
	if( !gPlayerTexture.loadFromFile( "images/player.bmp", gRenderer ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	if( !gProjTexture.loadFromFile( "images/projectile.bmp", gRenderer ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	if( !gShipTexture.loadFromFile( "images/ship.bmp", gRenderer ) )
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


list<Projectile*> Projects;

list<GameObject*> gameObjects;

vector< vector<Ships*> > ships(8, vector<Ships*>(10));


void addProj(Player pl)
{
	int x = pl.getPosX();
	Projectile * tmp = new Projectile(x, SCREEN_HEIGHT - gProjTexture.getHeight()*2);
    tmp->setTex(&gProjTexture);
	Projects.push_back(tmp);
    gameObjects.push_back(tmp);
}

int xx = 100, yy = 50;

void createArmy()
{

	for(vector<vector<Ships*>>::iterator it =  ships.begin(); it != ships.end(); ++it )
	{
		for(vector<Ships*>::iterator itt = (*it).begin(); itt != (*it).end(); ++itt)
		{
			Ships* tmp = new Ships(xx, yy);
			*itt = tmp;
			(*itt)->mPosX = xx;
			(*itt)->mPosY = yy;
			(*itt)->setTex(&gShipTexture);
			xx += 45;
		}
		yy += 30;
		xx = 100;
	}
}
	

void movingShips(int direction, bool hitScreenEnd)
{
	for(vector<vector<Ships*>>::iterator it =  ships.begin(); it != ships.end(); ++it )
	{
		for(vector<Ships*>::iterator itt = (*it).begin(); itt != (*it).end(); ++itt)
		{
			(*itt)->dir = direction;
			(*itt)->hitScreenEnd = hitScreenEnd;
			(*itt)->update();
		}
	}
}

bool ifScreenEndHit()
{
	bool beginersAlive = false;
	bool endHit = false;
	for(vector<vector<Ships*>>::iterator it =  ships.begin(); it != ships.end(); ++it )
	{
		for(vector<Ships*>::iterator itt = (*it).begin(); itt != (*it).end(); ++itt)
		{
			//if( (*itt)->dead == false )
			//	beginersAlive = true;
					
			if( ((*itt)->mPosX == 0) || ((*itt)->mPosX == SCREEN_WIDTH - gShipTexture.getWidth()) )
				return true;

		}
		//if(beginersAlive == false)

	}
	return endHit;
}


bool ifShipHit(int projX, int projY, int shipX, int shipY)
{
	if( (projX > (shipX - gShipTexture.getWidth()/2) && 
		(projX < (shipX + gShipTexture.getWidth()/2)) ) && 
		(projY > (shipY - gShipTexture.getHeight()/2)) && 
		(projY < (shipY + gShipTexture.getHeight()/2)) ) {
		//cout << " COLIDNA \n";
		//cout << " px " << projX << " py " << projY << " sx " << shipX << " sy " << shipY << endl;  
		return true;
	}
	else 
		return false;
}


void colliding()
{
	for(list<Projectile*>::iterator projIt = Projects.begin(); projIt != Projects.end(); ++projIt) 
				{

					for(vector<vector<Ships*>>::iterator it =  ships.begin(); it != ships.end(); ++it )
					{
						for(vector<Ships*>::iterator itt = (*it).begin(); itt != (*it).end(); ++itt)
						{
						
							if( ifShipHit( (*projIt)->getPosX(), (*projIt)->getPosY(), (*itt)->getPosX(), (*itt)->getPosY()) == true) {
								//cout << " PROJ = " << (*projIt)->getPosX() <<  
								(*itt)->dead = true;
							}
						}
					}
				}
}


int main( int argc, char* args[])
 {
	
//	 int i = 0;
	int timer = 0;
	int direction = 1;   //  1 : left moving / 2 : right
	bool screenHit = false;

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
        
			createArmy();

			
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

				
				timer += 1;     // not used yet
				//if( i == 10) 
				//{
				if(ifScreenEndHit()) {
					screenHit = true;
					direction += 1;
				}

				movingShips(direction, screenHit);
								
				if(screenHit)
					screenHit = false;

			
				colliding();



                // RENDERING
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
				SDL_RenderClear( gRenderer );


                
                for(std::list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end();)
                {
                    (*it)->render(gRenderer);
                    ++it;
                }
				
				for(vector<vector<Ships*>>::iterator it =  ships.begin(); it != ships.end(); ++it )
				{
					for(vector<Ships*>::iterator itt = (*it).begin(); itt != (*it).end(); ++itt)
					{
						if( (*itt)->dead == false )
							(*itt)->render(gRenderer);

					}
				}

				SDL_RenderPresent( gRenderer );
			}
		}
	
	}
	close();

	return 0;
}
