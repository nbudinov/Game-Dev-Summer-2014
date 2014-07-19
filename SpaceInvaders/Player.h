#include <SDL.h>


class Player
{
public:
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	static const int DOT_VEL = 10;

	Player();

	void handleEvent(SDL_Event& e);

	void move();

	void render(SDL_Renderer* gRenderer);


	int mPosX, mPosY;
	int mVelX, mVelY;
};
