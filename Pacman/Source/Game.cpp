	#include "Game.h"
#include "Player.h"
#include "Tile.h"
#include "LTexture.h"
#include "Screen.h"
#include "Mobs.h"

#include <stdio.h>
#include <fstream>

//Screen scrr;

	LTexture wallTexture;
	LTexture emptyTexture;
	LTexture dotTexture;
	LTexture redGhostTexture;
	LTexture blueGhostTexture;
	LTexture pinkGhostTexture;
	LTexture yellowGhostTexture;

Game::Game()
{
	gWindow = NULL;

	gRenderer = NULL;
}

bool Game::init()
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

bool Game::loadMedia()
{
	if( !wallTexture.loadFromFile( "Data/Art/wall.png", gRenderer ) )
	{
		printf(" failed to load wall \n ");
	}

	if( !emptyTexture.loadFromFile( "Data/Art/empty.png", gRenderer ) )
	{
		printf(" failed to load empty \n ");
	}

	if( !redGhostTexture.loadFromFile( "Data/Art/redghost.png", gRenderer ) )
	{
		printf(" failed to redGhost  \n ");
	}
	if( !blueGhostTexture.loadFromFile( "Data/Art/blueghost.png", gRenderer ) )
	{
		printf(" failed to redGhost  \n ");
	}
	if( !pinkGhostTexture.loadFromFile( "Data/Art/pinkghost.png", gRenderer ) )
	{
		printf(" failed to redGhost  \n ");
	}
	if( !yellowGhostTexture.loadFromFile( "Data/Art/yellowghost.png", gRenderer ) )
	{
		printf(" failed to redGhost  \n ");
	}


	//if( !playerTexture.loadFromFile( "images/player.png", gRenderer ) )
	//{
	//	printf(" failed to load player Texture \n ");
	//}


	return true;
}

bool Game::loadGhosts(Mobs *ghosts[])
{
	ghosts[0] = new Mobs(288, 288, 0);
	ghosts[1] = new Mobs(352, 288, 1);
	ghosts[2] = new Mobs(288, 320, 2);
	ghosts[3] = new Mobs(352, 320, 3);

	ghosts[0]->mobTexture = &redGhostTexture;
	ghosts[1]->mobTexture = &blueGhostTexture;
	ghosts[2]->mobTexture = &pinkGhostTexture;
	ghosts[3]->mobTexture = &yellowGhostTexture;
	

	return true;
}

bool Game::setTiles(Tile* tiles[])
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
				if(	tiles[t]->getType() == 0 ) 
				{
					tiles[t]->tileTex = &dotTexture;
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

bool Game::checkCollision( SDL_Rect A, SDL_Rect B )
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = A.x;
    rightA = A.x + A.w; 
    topA = A.y;
    bottomA = A.y + A.h;

    leftB = B.x ;
    rightB = B.x + B.w - 2 ;   
    topB = B.y ;
    bottomB = B.y + B.h -2  ;
	//printf( "%d  %d  %d  %d  %d  %d  \n", leftA, leftB, rightA, rightB, topA, topB  );
    if( bottomA <= topB ) {
        return false;
    }

    if( topA >= bottomB ) {
	//	printf("fail 2 \n");
        return false;
    }

    if( rightA <= leftB ) {
	//	printf("fail 3 \n");
        return false;
    }

    if( leftA > rightB ) {
	//	printf("fail 4 \n");
        return false;
    }
    return true;
}

int Game::Collision( Player player, Tile* tiles[] )
{
	for( int t = 0; t < 400; t++ )
	{
		if( checkCollision( player.getPlayerBox(), tiles[t]->getBox() ) == true )
		{
			if( tiles[t]->getType() == 1 )
			{
				switch(player.CurrentDirection)
				{
				case MovementLeft:
					//player.playerBox.x += PLAYER_SPEED;
					return 1;
					break;
				case MovementRight:
					//player.playerBox.x -= PLAYER_SPEED;
					return 2;
					break;
				case MovementUp:
					//player.playerBox.y += PLAYER_SPEED;
					return 3;
					break;
				case MovementDown:
					//player.playerBox.y -= PLAYER_SPEED;
					return 4;
					break;
				default:
					break;
				}
			}
		}
	}

	
return 0;
}

int Game::PlayerCollision( Player* player, Tile* tiles[])
{
	for( int t = 0; t < 400; t++ )
	{
		if( checkCollision( player->getPlayerBox(), tiles[t]->getBox() ) == true )
		{
			if( tiles[t]->getType() == 1 )
			{
				switch(player->CurrentDirection)
				{
				case MovementLeft:
					player->playerBox.x += PLAYER_SPEED;
					break;
				case MovementRight:
					player->playerBox.x -= PLAYER_SPEED;
					break;
				case MovementUp:
					player->playerBox.y += PLAYER_SPEED;
					break;
				case MovementDown:
					player->playerBox.y -= PLAYER_SPEED;
					break;
				default:
					break;
				}
			}

			if( tiles[t]->getType() == 0 )
			{
				tiles[t]->tileTex = &emptyTexture;
			}
		}
	}
	
return 0;
}


		
int Game::GhostsCollision(Mobs* ghosts[], Tile* tiles[])
{
	for( int t = 0; t < 400; t++ )
	{
		for( int i = 0; i < 4; i++ )
		{
	
			//printf( "%d , %d  \n", ghosts[i]->getMobBox().x, ghosts[i]->getMobBox().y  );
			//for( int i = 0; i < 4; i++ )
			//{			
			if( (checkCollision( ghosts[i]->getMobBox(), tiles[t]->getBox() ) == true) && (tiles[t]->getType() == 1) )
			{
				switch(ghosts[i]->mobDir)
				{
				case MoveLeft:
					//printf( "LQVOOOOOOOOOOOooO \n" );
					ghosts[i]->mobBox.x += 1;
					changeMobDir(ghosts[i]);
					break;
				case MoveRight:
				//	printf("AAAAAAAAAAAAa\n");
					ghosts[i]->mobBox.x -= 1;
					changeMobDir(ghosts[i]);
					break;
				case MoveUp:
					ghosts[i]->mobBox.y += 1;
					changeMobDir(ghosts[i]);
					break;
				case MoveDown:
					ghosts[i]->mobBox.y -= 1;
					changeMobDir(ghosts[i]);
					break;
				default:
					break;
				}
	
			}
		}
	}
return 0;
}

void Game::chase(Player player, Mobs* ghost)
{

}

void Game::changeMobDir(Mobs* ghost)
{
	int rand = std::rand() % 4;
	//printf("%d \n", rand);
	switch(rand)
	{
	case 0:
		ghost->mobDir = MoveLeft;
		break;
	case 1:
		ghost->mobDir = MoveRight;
		break;
	case 2:
		ghost->mobDir = MoveUp;
		break;
	case 3:
		ghost->mobDir = MoveDown;
		break;
	default: break;
	}
}

void Game::GhostsAI(Player player, Mobs* ghosts[], Tile* tiles[])
{
	for( int i = 0; i < 4; i++ )
	{
		switch( ghosts[i]->mobDir )
		{
		case MoveLeft:
		//	printf(" left \n ");
			ghosts[i]->mobBox.x -= 1;
			break;
		case MoveRight:
			printf(" right \n ");
			ghosts[i]->mobBox.x += 1;
			break;
		case MoveUp:
			printf(" up \n ");
			ghosts[i]->mobBox.y -= 1;
			break;
		case MoveDown:
			printf(" down \n ");
			ghosts[i]->mobBox.y += 1;
			break;
		default:
			break;
		}

		

	}



		
	/*	if( ghosts[i]->mobX > player.playerBox.x )
		{
			if( GhostsCollision( ghosts[i], tiles ) )
			{
				ghosts[i]->mobX -= 1;
				ghosts[i]->mobDir = MoveLeft;
			}
		}
		else
		{
			GhostsCollision( ghosts[i], tiles );	
				ghosts[i]->mobX += 1;
				ghosts[i]->mobDir = MoveRight;			
			
		}
			
		if( ghosts[i]->mobY > player.playerBox.y )
		{
			ghosts[i]->mobY -= 1;
			ghosts[i]->mobDir = MoveUp;
		}
		else
		{
			if( GhostsCollision( ghosts[i], tiles ) != 3 ) {
				printf( " RRRR \n" );
				ghosts[i]->mobY += 1;
			}
			ghosts[i]->mobDir = MoveDown;
		}
		
	*/
	
}

SDL_Renderer* Game::getRenderer()
{
	return gRenderer;
}





