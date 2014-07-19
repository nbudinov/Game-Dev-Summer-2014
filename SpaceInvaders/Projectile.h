#include <SDL.h>
#include <string>

class Projectile
{
public:
	static const int PROJ_WIDTH = 20;
	static const int PROJ_HEIGHT = 20;

	static const int PROJ_VEL = 10;

	Projectile();
	Projectile(int x);

	void handleEvent(SDL_Event& e);

	void move();

	void render(SDL_Renderer* gRenderer);

	int getPosY() {
		return mPosY;
	}

private:
	int mPosX, mPosY;
	int mVelY;

};