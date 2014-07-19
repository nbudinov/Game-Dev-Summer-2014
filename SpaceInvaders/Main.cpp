#include <iostream>

#include "Player.h"
#include "Projectile.h" 
#include "LTexture.h"

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <list>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;
 


LTexture gPlayerTexture;
LTexture gProjTexture;




Player::Player()
{
    mPosX = 0;
    mPosY = 0;

    mVelX = 0;
    mVelY = 0;
}

void Player::handleEvent( SDL_Event& e )
{
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            //case SDLK_UP: mVelY -= DOT_VEL; break;
            //case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            //case SDLK_UP: mVelY += DOT_VEL; break;
            //case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
    }
}

void Player::move()
{
    mPosX += mVelX;

    if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;

    }

}

void Player::render(SDL_Renderer* gRenderer)
{
    //Show the dot
	gPlayerTexture.render( mPosX, SCREEN_HEIGHT - DOT_HEIGHT, gRenderer );
}










Projectile::Projectile()
{
	mPosX = 0;
	mPosY = 0;
	mVelY = 10;
	
}
Projectile::Projectile(int x) 
{
	mPosX = x;
	mPosY = 0;
	mVelY = 10;
}

void Projectile::handleEvent(SDL_Event& e)
{
	if( e.type == SDL_KEYDOWN  )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_SPACE: 
				//addProj();
				//PROJ_NUMBER--;
			    //mVelY += PROJ_VEL; break;
		        //mVelX += PROJ_VEL; break;
				break;
        }
    }
    //If a key was released
   // else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    //{ 
     //   switch( e.key.keysym.sym )
     //   {
     //       case SDLK_SPACE: 
	//			mVelY -= PROJ_VEL; break;
				//mVelX -= PROJ_VEL; break;
				
	//	}

	
}

void Projectile::move()
{
	mPosY += mVelY;
	     if( ( mPosY < 0 ) || ( mPosY + PROJ_HEIGHT > SCREEN_HEIGHT ) )
	 {
        //Move back
	   mPosY -= mVelY;

     }

	cout << " Y = " << mPosY << " X = " << mPosX << endl;


}

void Projectile::render(SDL_Renderer* gRenderer)
{
	//cout << "rendering\n"; 

	gProjTexture.render(mPosX, mPosY, gRenderer);	
}







bool init()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
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
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if( !gPlayerTexture.loadFromFile( "images/dot.bmp", gRenderer ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	if( !gProjTexture.loadFromFile( "images/dot.bmp", gRenderer ) )
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

void addProj(Player pl)
{
	int x = pl.mPosX;
	Projectile* tmp = new Projectile(x);
	Projects.push_back(tmp);
}

	

int main( int argc, char* args[])
 {
	
	 int i = 0;


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

			Projectile Proj;
			Player player;
			//Projectile projects[10];

			//std::list<Projectile*>::iterator it = Projects.begin();


			while( !quit )
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					player.handleEvent( e );

					if( e.type == SDL_KEYDOWN )
					{
						
						switch( e.key.keysym.sym )
						{
							case SDLK_SPACE:
							{
								cout << "haha \n";
								//int xx = player.mPosX;
								addProj(player);
								//ammo--;
								
								break;
							}
						}
						
						//Projectiles[].handleEvent( e );
											
					}
				}

				player.move();
			
				//printf("= %d",proj.getPosY());
				int i = 0;
				for(std::list<Projectile*>::iterator it = Projects.begin(); it != Projects.end();)
				{
					cout << " = " << ++i << endl;
					(*it)->move();
					++it ;
					//Projects.remove(it)
				}
				
				for(std::list<Projectile*>::iterator it = Projects.begin(); it != Projects.end();)
				{
					//cout << " >>>> " << i << endl;
					(*it)->render(gRenderer);
					++it;
				}
				

				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				
				player.render(gRenderer);
				//(*it)->render(gRenderer);
				
				SDL_RenderPresent( gRenderer );
			}
		}
	
	}
	close();

	return 0;
}
