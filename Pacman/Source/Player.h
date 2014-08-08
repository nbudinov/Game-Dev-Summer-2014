
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

	Player(int x, int y);

	bool handleEvent(SDL_Event& e);

    void update();

	void render(SDL_Renderer* gRenderer = NULL);

	int getPlayerX();

	int getPlayerY();
	
	int getDir();
	
	void setPlayerTex( LTexture* tex );

	SDL_Rect getPlayerBox();


private:

};
