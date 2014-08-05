#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_image.h>
	#include <SDL_ttf.h>
#elif __APPLE__
#include <Sdl2/sdl.h>
#include <sdl2_image/sdl_image.h>
#endif

#include <vector>
#include <list>
#include "LTexture.h"
#include "ScreenConsts.h"
#include "Tile.h"
#include "Player.h"
#include "Game.h"
#include "Timer.h"
#include "Vector2.h"

#include<fstream>
#include <stdio.h>

using namespace std;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

LTexture background;
LTexture brick;
LTexture yellow;
LTexture playerTexture;
LTexture coinTexture;
LTexture trapTexture;
LTexture SpriteSheetTexture;

SDL_Rect gSpriteClips[10];

bool init()
{
	
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        return false;
	}

    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        printf( "Warning: Linear texture filtering not enabled!" );
    }

    gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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

bool loadMedia()
{
	if( !SpriteSheetTexture.loadFromFile( "images/PlayerSpriteSheet.png" , gRenderer) ) {
		printf("spriteSheet Err \n");
		return false;
	}
	else
	{
		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 0;
		gSpriteClips[0].w = 32;
		gSpriteClips[0].h = 32;

		gSpriteClips[1].x = 32;
		gSpriteClips[1].y = 0;
		gSpriteClips[1].w = 32;
		gSpriteClips[1].h = 32;

		gSpriteClips[2].x = 64;
		gSpriteClips[2].y = 0;
		gSpriteClips[2].w = 32;
		gSpriteClips[2].h = 32;

		gSpriteClips[3].x = 96;
		gSpriteClips[3].y = 0;
		gSpriteClips[3].w = 32;
		gSpriteClips[3].h = 32;

		gSpriteClips[4].x = 128;
		gSpriteClips[4].y = 0;
		gSpriteClips[4].w = 32;
		gSpriteClips[4].h = 32;

		gSpriteClips[5].x = 0;
		gSpriteClips[5].y = 32;
		gSpriteClips[5].w = 32;
		gSpriteClips[5].h = 32;

		gSpriteClips[6].x = 32;
		gSpriteClips[6].y = 32;
		gSpriteClips[6].w = 32;
		gSpriteClips[6].h = 32;

		gSpriteClips[7].x = 64;
		gSpriteClips[7].y = 32;
		gSpriteClips[7].w = 32;
		gSpriteClips[7].h = 32;

		gSpriteClips[8].x = 96;
		gSpriteClips[8].y = 32;
		gSpriteClips[8].w = 32;
		gSpriteClips[8].h = 32;

		gSpriteClips[9].x = 128;
		gSpriteClips[9].y = 32;
		gSpriteClips[9].w = 32;
		gSpriteClips[9].h = 32;

	}

	if ( !background.loadFromFile("images/background.png", gRenderer) ){
		printf("cant load background.png ");
		return false;
	}

	if( !brick.loadFromFile("images/brick.png", gRenderer) ){
		printf("cant load brick.png ");
		return false;
	}

	if( !yellow.loadFromFile("images/yellow.png", gRenderer) ){
		printf("cant load yellow.png ");
		return false;
	}
	
	if( !playerTexture.loadFromFile("images/dot.bmp", gRenderer) ){
		printf("cant load dot.png ");
		return false;
	}
	
	if( !coinTexture.loadFromFile("images/coin.bmp", gRenderer) ){
		printf("cant load coin.png ");
		return false;
	}

	if( !trapTexture.loadFromFile("images/trap.bmp", gRenderer) ){
		printf("cant load trap.png ");
		return false;
	}


	return true;
}

void close()
{
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//IMG_Quit();
	SDL_Quit();
}

bool ifCollides(int playerX, int playerY, int objX, int objY)
{
	if( (playerX + TILE_SIZE) > objX &&
		playerX < (objX + TILE_SIZE) && 
		(playerY + TILE_SIZE) > objY &&
		playerY < ( objY + TILE_SIZE ) )
	{
		return true;
	}
	else
		return false;
}


Game game;


bool Game::check_collision( SDL_Rect A, SDL_Rect B )
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

	//printf( "%d  %d  %d  %d  %d  %d  \n", leftA, leftB, rightA, rightB, topA, topB  );

    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
		///printf("fail 2 \n");
        return false;
    }

    if( rightA <= leftB )
    {
		//printf("fail 3 \n");
        return false;
    }

    if( leftA >= rightB )
    {
		//printf("fail 4 \n");
        return false;
    }
    return true;
}


bool Game::setTiles( Tile *tiles[] )
{
    int x = 0, y = 0;

    std::ifstream map( "images/map.txt" );

    if( map == NULL )
    {
        return false;
    }

    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        int tileType = -1;

        map >> tileType;

        if( map.fail() == true )
        {
            map.close();
			printf("failed 1 \n");
            return false;
        }

		if(tileType >= 0 || tileType < 3) {
			tiles[ t ] = new Tile( x, y, tileType );
			//printf("x = %d   y = %d", x, y);
			if(	tiles[t]->getType() == 1 ) 
			{
			//	printf("TUKAAAAA\n");
				tiles[t]->tileTex = &brick;
			}
			else if(tiles[t]->getType() == 2)
			{
				tiles[t]->tileTex = &coinTexture;				
			}
			else if(tiles[t]->getType() == 3)
			{
				tiles[t]->tileTex = &trapTexture;
			}
			else
				tiles[t]->tileTex = &yellow;
		}    
		else 
			printf("ne baca \n");

        x += TILE_WIDTH;

        if( x >= LEVEL_WIDTH )
        {
            x = 0;

            y += TILE_HEIGHT;
        }
    }

    map.close();
	return true;
}

int newCollision( SDL_Rect player, SDL_Rect tile )
{
	int playerLeft = player.x;
    int playerRight = player.x + player.w;
    int playerTop = player.y;
    int playerBottom = player.y + player.h;

    int tileLeft = tile.x;
    int tileRight = tile.x + tile.w;
    int tileTop = tile.y;
    int tileBottom = tile.y + tile.h;

	int dX = 0,	dY = 0;

	if (playerRight >= tileRight && playerBottom >= tileBottom ) 
	{
		printf("dolu - dqsno \n");
		dX = playerRight - tileRight;
		dY = playerBottom - tileBottom;
		if( dX > dY )
			return 1;
		else
			return 2;
	}
	else if( playerLeft <= tileLeft && playerBottom >= tileBottom )
	{
		printf("dolu - lqvo \n");
		dX = tileLeft - playerLeft ;
		dX = playerBottom - tileBottom ;
		if( dX > dY )
			return 3;
		else
			return 4;		
	}
	else if( playerLeft <= tileLeft && playerTop <= tileTop )
	{
		printf("gore - lqvo \n");
		dX = tileLeft - playerLeft;
		dY = tileTop - playerTop;
		if( dX > dY )
			return 5;
		else
			return 6;
	}
	else if( playerRight >= tileRight && playerTop <= tileTop )
	{
		printf("gore - dqsno \n");
		dX = playerRight - tileRight;
		dY = tileTop - playerTop;
		if( dX > dY )
			return 7;
		else 
			return 8;
	}
	else 
	
	printf( " AT THE END" );
return 0;
}

int Game::Collision( Player player, Tile* tiles[] )
{
	for( int t = 0; t < TOTAL_TILES; t++ )
	{
		if( tiles[t]->getType() == 2 )
		{
			if( game.check_collision( player.playerBox, tiles[t]->getBox() ) == true )
			{
				tiles[t]->tileTex = &yellow;
				return 2;		
			}
		}
		else if( tiles[t]->getType() == 3 )
		{
			if( game.check_collision( player.playerBox, tiles[t]->getBox() ) == true )
			{
				printf(" FIRE \n");
				//player.playerBox.x = 0;
				//player.playerBox.y = 0;
				return 3;
			}
		}
	}

	//return 0;
}


int main( int argc, char* args[])
{
	//test();
	//system("pause")
	//return 0;

	//int totalTiles = TOTAL_TILES;
	Tile *tiles[690];
	
	if(	game.setTiles(tiles) == false) {
		printf("set tiles err \n");	
	}

	if( !init() )	{
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

			Player player(20, 30);
			player.playerTex = &playerTexture;
			
			Timer timer;
			Uint32 oldTime = 0;
			Uint32 currentTime = 0;

			int anim = 0;
			int movementLeftFrame = 0;
			int movementRightFrame = 5;
			int lastTurningWay = 1;  // 1 - left / 2 - right

			while( !quit )
			{
				timer.start();

				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					
					player.handleEvent(e);

				}
           
				player.update();

				player.playerBox.y += GRAVITY;
						
				game.Collision(player, tiles) ;
			
				if( game.Collision(player, tiles) == 3)
				{
					player.playerBox.x = 0;
					player.playerBox.y = 0;

				}

				for( int t = 0; t < TOTAL_TILES; t++ )
				{
					if( tiles[t]->getType() == 1 )
					{
						if( game.check_collision( player.playerBox, tiles[t]->getBox() ) == true )
						{
							if( newCollision( player.playerBox, tiles[t]->getBox() ) == 1 || newCollision( player.playerBox, tiles[t]->getBox() ) == 7 )
							{
								player.playerBox.x += PLAYER_SPEED;
							}
							else
							if( newCollision( player.playerBox, tiles[t]->getBox() ) == 2 || newCollision( player.playerBox, tiles[t]->getBox() ) == 4  )
							{
								player.playerBox.y += JUMP_VEL + 5; 
							}
							else
							if( newCollision( player.playerBox, tiles[t]->getBox() ) == 3 || newCollision( player.playerBox, tiles[t]->getBox() ) == 5 )
							{
								player.playerBox.x -= PLAYER_SPEED;
							}
							else
							if( newCollision( player.playerBox, tiles[t]->getBox() ) == 6 || newCollision( player.playerBox, tiles[t]->getBox() ) == 8 )
							{								
								player.playerBox.y -= GRAVITY;
							}
						 }
					}
				}
				
				anim++;
				if(anim > 100)
					anim = 0;

				//oldTime = currentTime;
				//printf("SS = %d \\ new time = %d, old time = %d \n",timer.getTicks(), currentTime, oldTime);

				//currentTime = timer.getTicks();
				//if(currentTime - oldTime > 2)
				//{
						//printf("hoho \n");
						//oldTime = currentTime;
						// currentTime = timer.getTicks();
				//}			

				SDL_Rect* currentClip;
				if( player.mDirection == MovementStand )
				{
					//if(anim % 5 == 0)
					//{
					//	oldTime = currentTime;
					//	currentTime = timer.getTicks();
					//}
					if( lastTurningWay == 1 )
						currentClip = &gSpriteClips[0];
					else if(lastTurningWay = 2)
						currentClip = &gSpriteClips[5];
				}
				else 
				{
					bool pace = anim % 20 > 10;

					if( player.mDirection == MovementLeft )
					{
						if(anim % 5 == 0)
						{
							//oldTime = currentTime;
							//currentTime = timer.getTicks();
							if(movementLeftFrame >= 4)
								movementLeftFrame = 0;	
							else
								movementLeftFrame++ ;
							//printf(" LEFT = %d \n", movementLeftFrame);
						}
						currentClip = &gSpriteClips[movementLeftFrame];
						lastTurningWay = 1;
					}
					if( player.mDirection == MovementRight )
					{
						if(anim % 5 == 0)
						{
							//oldTime = currentTime;
							//currentTime = timer.getTicks();
							if(movementRightFrame >= 9)
								movementRightFrame = 5;	
							else
								movementRightFrame++ ;
							//printf( " RIGHT = %d \n ", movementRightFrame  );
						}
	
						currentClip = &gSpriteClips[movementRightFrame];
						lastTurningWay = 2;
					}
				}
				

				

				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0x00 );
				SDL_RenderClear( gRenderer );

		        // RENDERING
				for(int i = 0; i < TOTAL_TILES; i++) {
					tiles[i]->show(gRenderer);
				}
				
				SpriteSheetTexture.NewRender(player.playerBox.x, player.playerBox.y, currentClip, gRenderer);

				SDL_RenderPresent( gRenderer );

			}
		}
	}
	
	
	//system("pause");
	return 0;
}












