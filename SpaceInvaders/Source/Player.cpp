
//#ifdef WIN32
    #include <SDL.h>
    #include <SDL_image.h>
//#elif __APPLE__
//    #include <SDL2/SDL.h>
//    #include <SDL2_image/SDL_image.h>
//#endif

#include "Player.h"
#include "GameObject.h"


static const int DOT_VEL = 10;


Player::Player(int x, int y)
    : GameObject(x , y)
{
    mDirection = MovementStand;
	//alive = true;
}

bool Player::handleEvent( SDL_Event& e )
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
         switch( e.key.keysym.sym )
         {
             case SDLK_LEFT:
                 mDirection = MovementLeft;
                 break;
             case SDLK_RIGHT:
                 mDirection = MovementRight;
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
                break;
            case SDLK_RIGHT:
                if (mDirection == MovementRight)
                     mDirection = MovementStand;
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
    switch (mDirection) {
        case MovementLeft:
            mPosX -= DOT_VEL;
            break;
        case MovementRight:
            mPosX += DOT_VEL;
            break;
        case MovementStand:
        default:
            break;
    }
}
