
#ifndef _GAMEOBJECT
#define _GAMEOBJECT

#include <SDL.h>
class LTexture;

class GameObject {
public:
	bool alive;

    GameObject(int x, int y);
    
    int getPosY();
    int getPosX();
    void move(int x, int y);

    void setTex(LTexture * tex);
    
    virtual void update() = 0;
    void render(SDL_Renderer * renderer);
    
//protected:
    int mPosX,mPosY;
    LTexture * mTex;
};


#endif /* GAMEOBJECT */