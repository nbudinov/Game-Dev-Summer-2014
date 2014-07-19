/*
#include <Projectile.h>
#include <LTexture.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

LTexture gProjTexture;


Projectile::Projectile()
{
	mPosX = 0;
	mPosY = SCREEN_HEIGHT;
	mVelX = 0;
	mVelY = 0;
	
}
Projectile::Projectile(int x) 
{
	mPosX = x;
	mPosY = SCREEN_HEIGHT;
	mVelX = 0;
	mVelY = 0;
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
	mPosY -= mVelY;

     if( ( mPosY < 0 ) || ( mPosY + PROJ_HEIGHT > SCREEN_HEIGHT ) )
	 {
        //Move back
	   mPosY -= mVelY;
     }

}

void Projectile::render(SDL_Renderer* gRenderer)
{
	gProjTexture.render(mPosX, mPosY, gRenderer);	
}
*/