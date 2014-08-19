
#include <SDL.h>

class LTexture;

typedef enum {
    MoveStand,
    MoveLeft,
    MoveRight,
	MoveUp,
	MoveDown,
} Move;

class Mobs
{
public:
	LTexture* mobTexture;
	int mobX, mobY;
	SDL_Rect mobBox;
	Move mobDir;

	Mobs(int x, int y, int type);

	void changeDir();

	void render(SDL_Renderer* gRenderer);

	SDL_Rect getMobBox();

private:
	int mobType;

};