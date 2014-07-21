#include <iostream>

#include <SDL_ttf.h>
#include "ScreenConsts.h"
#include <GameObject.h>
#include "Player.h"
#include "Projectile.h" 
#include "LTexture.h"
#include "Ships.h"
#include <SDL_ttf.h>

//#ifdef WIN32
#include <SDL.h>
#include <SDL_image.h>
TTF_Font* gFont = NULL;
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
LTexture gLoseScreen;
LTexture gPlayerLifesTexture;

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

		if( TTF_Init() == -1 ){
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					return false;
				}

    return true;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	gFont = TTF_OpenFont( "images/lazy.ttf", 22 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 0xFF, 0xFF, 0 };
		if( !gPlayerLifesTexture.loadFromRenderedText( " Lifes: ", textColor, gRenderer, gFont ) )
		{
			printf( "Failed to render text texture!\n" );
			success = false;
		}
	}

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

	if( !gLoseScreen.loadFromFile( "images/losescreen.png", gRenderer ) )
	{
		printf( "Failed to load LoSE screen texture!\n" );
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

vector<Projectile*> shipProjects;

void addProj(Player pl)
{
	int x = pl.getPosX();
	Projectile * tmp = new Projectile(x, SCREEN_HEIGHT - gProjTexture.getHeight()*2);
    tmp->setTex(&gProjTexture);
	Projects.push_back(tmp);
    gameObjects.push_back(tmp);
}

void addShipProj(int shipX, int shipY)
{
	Projectile * tmp = new Projectile(shipX, shipY);
    tmp->setTex(&gProjTexture);
	shipProjects.push_back(tmp);
}

void shipFire()
{
	int randomShip = rand() % 79;

	for(vector<vector<Ships*>>::iterator it =  ships.begin(); it != ships.end(); ++it )
	{
		for(vector<Ships*>::iterator itt = (*it).begin(); itt != (*it).end(); ++itt)
		{
			if( (*itt)->alive == true ) {
				if( (*itt)->shipNum == randomShip)
				{
					addShipProj( (*itt)->mPosX, (*itt)->mPosY );
					(*itt)->shooting = true;
				}
			}
		}
	}
}

//int xx = 100, yy = 50, number = 0;

void createArmy(int xx, int yy, int number)
{
	for(vector<vector<Ships*>>::iterator it =  ships.begin(); it != ships.end(); ++it )
	{
		for(vector<Ships*>::iterator itt = (*it).begin(); itt != (*it).end(); ++itt)
		{
			Ships* tmp = new Ships(xx, yy, number);
			*itt = tmp;
			(*itt)->mPosX = xx;
			(*itt)->mPosY = yy;
			(*itt)->setTex(&gShipTexture);
			xx += 55;
			number += 1;
		}
		yy += 30;
		xx = 100;
	}
}
	

void movingShips(int direction, bool hitScreenEnd)
{
	vector<vector<Ships*>>::iterator iter =  ships.end()-1;
	for(vector<Ships*>::iterator itterator = (*iter).begin(); itterator != (*iter).end(); ++itterator)
	{
		if( (*itterator)->mPosY == SCREEN_HEIGHT - 150 )
			hitScreenEnd = false;
	}


	for(vector<vector<Ships*>>::iterator it =  ships.begin(); it != ships.end(); ++it )
	{
		for(vector<Ships*>::iterator itt = (*it).begin(); itt != (*it).end(); ++itt)
		{
			(*itt)->dir = direction;
			(*itt)->hitScreenEnd = hitScreenEnd;
			if( (*itt)->alive == true ) 
			{
				(*itt)->update();
			}
		}
	}
}

bool ifScreenEndHit()
{
	//int firstLeftAlive = 0, firstRightAlive = 0;
	bool endHit = false;
	
	vector<vector<Ships*>>::iterator it = ships.begin();
		for(vector<Ships*>::reverse_iterator itt = (*it).rbegin(); itt != (*it).rend(); ++itt)
		{

	if( (*itt)->mPosX == 0 || (*itt)->mPosX == SCREEN_WIDTH - gShipTexture.getWidth() )
	{
		return true;			
	}
		}
	return endHit;
}


bool ifShipHit(int projX, int projY, int shipX, int shipY)
{
	if ( projX >= shipX  && 
		(projX < (shipX + (gShipTexture.getWidth()) ) )  && 
		(projY > shipY  ) && 
		(projY < (shipY + (gShipTexture.getHeight()) ) ) )
	{
	return true;
	}
	else 
		return false;
}


void ifProjCollShip()
{	
	for(list<Projectile*>::iterator projIt = Projects.begin(); projIt != Projects.end(); ++projIt) 
	{	
		if( (*projIt)->alive == true ) 
		{
			for(vector<vector<Ships*>>::iterator it =  ships.begin(); it != ships.end(); ++it )
			{
				for(vector<Ships*>::iterator itt = (*it).begin(); itt != (*it).end(); ++itt)
				{	
					if( (*itt)->alive == true )
					{
						if( ifShipHit( (*projIt)->mPosX, (*projIt)->mPosY, (*itt)->mPosX, (*itt)->mPosY) == true) 
						{
							(*itt)->alive = false;
							(*projIt)->alive = false;
							//delete (*projIt);
							//Projects.resize(Projects.size()-1);
							//delete (*projIt);							
						}
					}
				}
			}
		}
	}
}

bool ifHitPlayer(int playerX, int playerY, int shipProjX, int shipProjY)
{
	//cout << "px " << playerX << "py " << playerY << "sX" << shipProjX << "sY " << shipProjY << endl;
	if( shipProjX > playerX  &&
		shipProjX < playerX + gPlayerTexture.getWidth()  &&
		shipProjY > playerY - gPlayerTexture.getHeight()  )
	{
		cout << "curna TRUE";
		return true;
	}
	else {
		return false;
	}
}

void projCollPlayer(Player player, int &playerLifes)
{
	if(playerLifes > 0) {
		for(vector<Projectile*>::iterator projIt = shipProjects.begin(); projIt != shipProjects.end(); ++projIt) 
		{
			if (ifHitPlayer(player.mPosX, player.mPosY, (*projIt)->mPosX, (*projIt)->mPosY ) ) {
				playerLifes -= 1;
				(*projIt)->alive = false;
				delete (*projIt);
			}
			else if( (*projIt)->mPosY > SCREEN_HEIGHT ) 
			{
				(*projIt)->alive = false;
				//delete (*projIt);
			}
		}
	}
}

void deleteShips()
{
	for(vector<vector<Ships*>>::iterator it =  ships.begin(); it != ships.end(); ++it )
	{
		for(vector<Ships*>::iterator itt = (*it).begin(); itt != (*it).end(); ++itt)
		{
			//if( (*itt)->dead == true )
				(*itt)->alive = false;
				delete (*itt);
		}
	}
	
}

int main( int argc, char* args[])
 {
	SDL_Color textColor = { 255, 255, 200, 255 };
//	 int i = 0;
	int timer = 0;
	int direction = 1;   //  1 : left moving / 2 : right
	bool screenHit = false;

	int PlayerLifes = 3;

	std::stringstream PlayerLifesText;

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
        
			createArmy(100, 50, 0);

			while( !quit )
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					//if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_n) 
					//{
					//	PlayerLifes = 1;
					//	deleteShips();
					//	createArmy(100, 50, 0);
					//}
					bool shouldShoot = player.handleEvent( e );
                    if (shouldShoot)
                        addProj(player);
					
				}
           
			if(PlayerLifes <= 0) {
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
				SDL_RenderClear( gRenderer );

				gLoseScreen.render(0, 0, gRenderer);

			}
			else 
			{
				PlayerLifesText.str("");
				PlayerLifesText << "Lifes " << PlayerLifes;

				gPlayerLifesTexture.loadFromRenderedText( PlayerLifesText.str().c_str(), textColor, gRenderer, gFont  ); 

				if( timer > 100 )
					timer = 0;
				timer += 1; 

				if( timer % 3 == 0) 
				{
					if(ifScreenEndHit()) {
						screenHit = true;
						direction += 1;
					}	
				
					movingShips(direction, screenHit);
				
					if(screenHit)
						screenHit = false;
				}				
				
				if( timer % 50 == 0) {
					shipFire();
				}

				ifProjCollShip();
				projCollPlayer(player, PlayerLifes);
				
				//cout << PlayerLifes << endl;

				  for(std::list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end();)
				  {
					if( (*it)->alive == true ) 
						(*it)->update();
					    ++it;
					
				  }

				for(vector<Projectile*>::iterator it = shipProjects.begin(); it != shipProjects.end(); ++it)
				{
					if( (*it)->alive == true)
						(*it)->move();
				}

                // RENDERING
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
				SDL_RenderClear( gRenderer );

				for(vector<Projectile*>::iterator it = shipProjects.begin(); it != shipProjects.end(); ++it)
				{
						if( (*it)->alive == true)
							(*it)->render(gRenderer);
				}
	                
                for(std::list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end();)
                {
					if ((*it)->alive == true ) 
					    (*it)->render(gRenderer);
                    ++it;
					
                }
				
				for(vector<vector<Ships*>>::iterator it =  ships.begin(); it != ships.end(); ++it )
				{
					for(vector<Ships*>::iterator itt = (*it).begin(); itt != (*it).end(); ++itt)
					{
						if( (*itt)->alive == true )
							(*itt)->render(gRenderer);

					}
				}
			}

			gPlayerLifesTexture.render(5, 5, gRenderer);

				SDL_RenderPresent( gRenderer );
				//deleteDeadShips(); m

			}
		}
	
	}
	close();
	//system("pause");
	return 0;
}
