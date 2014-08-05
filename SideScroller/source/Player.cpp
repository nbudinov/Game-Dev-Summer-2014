#include <iostream>

#include "Player.h"
#include "ScreenConsts.h"
#include "LTexture.h"
#include "Game.h"

/* Function prototype for the timer callback function  typedef Uint32 (*SDL_TimerCallback)(Uint32 interval);*/

Uint32 stopJump(Uint32 interval, void * param)
{
	Player * p = (Player*)param;
	p->velY += JUMP_VEL;
	return 0;
}

Player::Player(int x, int y)
{
	playerBox.x = x;
	playerBox.y = y;

	playerBox.w = TILE_WIDTH;
	playerBox.h = TILE_HEIGHT;

    mDirection = MovementStand;
	jumpHeight = 0;
	velX = 0;
	velY = 0;
}

bool Player::handleEvent( SDL_Event& e )
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    { 
         switch( e.key.keysym.sym )
         {
             case SDLK_LEFT:
                 mDirection = MovementLeft;
				 velX -= 3;
                 break;
             case SDLK_RIGHT:
                 mDirection = MovementRight;
				 velX += 3;
                break;
			 case SDLK_SPACE:
				//if(jumpHeight == 20) {
					mDirection = MovementJump;
					jumpHeight = 20; 
					velY -= JUMP_VEL;
				//}

					SDL_AddTimer(250, stopJump, this);
				 break;
            default:
                 break;
         }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_LEFT:
                if (mDirection == MovementLeft) 
                    mDirection = MovementStand;
				velX += 3;
                break;
            case SDLK_RIGHT:
                if (mDirection == MovementRight)
                     mDirection = MovementStand;
				velX -= 3;
                break;
			case SDLK_SPACE:
		//		if (mDirection == MovementJump)
          //          mDirection = MovementStand;
				//velY -= 8;
               break;
            default:
                break;
        }
    }
    
    return e.type == SDL_KEYUP &&
            e.key.keysym.sym == SDLK_SPACE;
}

void Player::update()
{
	//   switch (mDirection) {
	//		case MovementLeft:
			
	//		break;
	//       case MovementRight:
	//			playerBox.x += PLAYER_SPEED;    
	//		break;
			//case MovementJump:
			//	playerBox.y -= PLAYER_SPEED;
			//	break;
	 //       case MovementStand:
	  //      default:
	   //         break;
	//	}
		if(jumpHeight > 0)
		{
			playerBox.y -= GRAVITY+4;
			jumpHeight -= 2 ;
		}

		playerBox.x += velX;
		playerBox.y += velY;

}

void Player::render(SDL_Renderer* gRenderer)
{
	playerTex->render(playerBox.x, playerBox.y, gRenderer);
}

int Player::getPlayerX()
{
	return playerBox.x;
}

int Player::getPlayerY()
{
	return playerBox.y;
}

SDL_Rect Player::getPlayerBox()
{
	return playerBox;
}


