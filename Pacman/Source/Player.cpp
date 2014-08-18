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

    CurrentDirection = MovementStand;

	directionX = 0;
	directionY = 0;
	turnDir = 0;

	score = 0;

	//playerTex.loadFromFile( "images/player.png",  )
}

bool Player::handleEvent( SDL_Event& e )
{
    if( e.type == SDL_KEYDOWN )
    { 
         switch( e.key.keysym.sym )
         {
            case SDLK_LEFT:
				CurrentDirection = MovementLeft;
				turnDir = 4;
				break;
			case SDLK_RIGHT:
				CurrentDirection = MovementRight;
				turnDir = 2;
				break;
			case SDLK_UP:
				CurrentDirection = MovementUp;
				turnDir = 1;
				break;
			case SDLK_DOWN:
				CurrentDirection = MovementDown;
				turnDir = 3;
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
	   switch (CurrentDirection) {
			case MovementLeft:
				directionX = 4;
				playerBox.x -= PLAYER_SPEED;
				break;
			case MovementRight:
				directionX = 2;
				playerBox.x += PLAYER_SPEED;    
				break;
			case MovementUp:
				directionY = 1;
				playerBox.y -= PLAYER_SPEED;
				break;
			case MovementDown:
				directionY = 3;
				playerBox.y += PLAYER_SPEED;
				break;
	      case MovementStand:
	        default:
	           break;
		}
		

		//playerBox.x += velX;
		//playerBox.y += velY;
}

void Player::render(SDL_Renderer* gRenderer, SDL_RendererFlip flip, int w, int h)
{
	playerTex->render(playerBox.x, playerBox.y, gRenderer, flip, w, h);
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


