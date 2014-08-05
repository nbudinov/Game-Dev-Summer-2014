
#include <SDL.h>

class LTexture;

typedef enum {
    MovementStand,
    MovementLeft,
    MovementRight,
	MovementJump,
} Movement;

class Player
{
public:
	int jumpHeight;
	LTexture* playerTex;
	SDL_Rect playerBox;
    Movement mDirection;
	float velX, velY;

	Player(int x, int y);

	bool handleEvent(SDL_Event& e);

    void update();

	void render(SDL_Renderer* gRenderer = NULL);

	int getPlayerX();

	int getPlayerY();
	
	int getDir();
	
	SDL_Rect getPlayerBox();


private:

};
