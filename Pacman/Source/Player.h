
#include <SDL.h>

class LTexture;

typedef enum {
    MovementStand,
    MovementLeft,
    MovementRight,
	MovementUp,
	MovementDown,
} Movement;

class Player
{
public:
	LTexture* playerTex;
	SDL_Rect playerBox;
    Movement CurrentDirection;
	Movement NewDirection;

	float velX, velY;

	int directionX, directionY, turnDir;

	Player(int x, int y);

	bool handleEvent(SDL_Event& e);

    void update();

	void render(SDL_Renderer* gRenderer, SDL_RendererFlip flip, int w, int h);

	int getPlayerX();

	int getPlayerY();
	
	int getDir();
	
	void setPlayerTex( LTexture* tex );

	SDL_Rect getPlayerBox();

	int score;


};
