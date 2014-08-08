#include "Game.h"
#include "Player.h"
#include "Tile.h"

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

    leftB = B.x + 2;
    rightB = B.x + B.w - 2;   
    topB = B.y + 2;
    bottomB = B.y + B.h - 2;
	//printf( "%d  %d  %d  %d  %d  %d  \n", leftA, leftB, rightA, rightB, topA, topB  );
    if( bottomA <= topB ) {
        return false;
    }

    if( topA >= bottomB ) {
		///printf("fail 2 \n");
        return false;
    }

    if( rightA <= leftB ) {
		//printf("fail 3 \n");
        return false;
    }

    if( leftA > rightB ) {
		//printf("fail 4 \n");
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
				switch(player.mDirection)
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