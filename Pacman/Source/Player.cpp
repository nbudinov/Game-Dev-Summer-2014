#include <iostream>

#include "Player.h"
#include "ScreenConsts.h"
#include "LTexture.h"
#include "Game.h"

Player::Player(int x, int y)
{
	playerBox.x = x;
	playerBox.y = y;

	playerBox.w = TILE_WIDTH;
	playerBox.h = TILE_HEIGHT;

    mDirection = MovementStand;

	//playerTex.loadFromFile( "images/player.png",  )
}

bool Player::handleEvent( SDL_Event& e )
{
    if( e.type == SDL_KEYDOWN )
    { 
         switch( e.key.keysym.sym )
         {
             case SDLK_LEFT:
					mDirection = MovementLeft;
					break;
				case SDLK_RIGHT:
					mDirection = MovementRight;
					break;
				case SDLK_UP:
					mDirection = MovementUp;
					break;
				case SDLK_DOWN:
					mDirection = MovementDown;
					break;
				default:
					break;
         }
    }
   /* else if( e.type == SDL_KEYUP )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_LEFT:
                if (mDirection == MovementLeft) 
                    mDirection = MovementStand;
				//velX += 3;
                break;
            case SDLK_RIGHT:
                if (mDirection == MovementRight)
                     mDirection = MovementStand;
				velX -= 3;
                break;
	        default:
                break;
        }
    }
   */ 
    return e.type == SDL_KEYUP &&
            e.key.keysym.sym == SDLK_SPACE;
}

void Player::update()
{
	   switch (mDirection) {
			case MovementLeft:
				playerBox.x -= PLAYER_SPEED;
				break;
			case MovementRight:
				playerBox.x += PLAYER_SPEED;    
				break;
			case MovementUp:
				playerBox.y -= PLAYER_SPEED;
				break;
			case MovementDown:
				playerBox.y += PLAYER_SPEED;
				break;
	      case MovementStand:
	        default:
	           break;
		}
		

		//playerBox.x += velX;
		//playerBox.y += velY;



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

void Player::setPlayerTex(LTexture* tex)
{
	playerTex = tex;
}

SDL_Rect Player::getPlayerBox()
{
	return playerBox;
}

