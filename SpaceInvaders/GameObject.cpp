#include "GameObject.h"
#include "LTexture.h"

GameObject::GameObject(int x, int y)
{
    mPosY = y;
    mPosX = x;
}

int GameObject::getPosY()
{
    return mPosY;
}

int GameObject::getPosX()
{
    return mPosX;
}

void GameObject::move(int x, int y)
{
    mPosX = x;
    mPosY = y;
}

void GameObject::setTex(LTexture * tex)
{
    mTex = tex;
}

void GameObject::render(SDL_Renderer * renderer)
{
    mTex->render(mPosX, mPosY, renderer);
}