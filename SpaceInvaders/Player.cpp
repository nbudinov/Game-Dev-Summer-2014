/*
#include "Player.h"
#include "Projectile.h" 
#include "LTexture.h"

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <list>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


LTexture gPlayerTexture;


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
    //If a key was released
//    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
  //  {
        //Adjust the velocity
    //    switch( e.key.keysym.sym )
   //     {
            //case SDLK_UP: mVelY += DOT_VEL; break;
            //case SDLK_DOWN: mVelY -= DOT_VEL; break;
      //      case SDLK_LEFT: mVelX += DOT_VEL; break;
    //        case SDLK_RIGHT: mVelX -= DOT_VEL; break;
      //  }
    //}
}

void Player::move()
{
    mPosX += mVelX;

    //If the player went too far to the left or right
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
*/